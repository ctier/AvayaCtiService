#include "stdafx.h"
#include "KafkaConsumer.h"

KafkaConsumer::KafkaConsumer(const std::string& brokers, const std::string& topics, std::string groupid/*, int64_t offset*/)
    :brokers(brokers),
    topics(topics),
    groupid(groupid)
    //,offset_(offset)
{
	/*
    last_offset_ = 0;
    kafka_consumer_ = NULL;
    topic_ = NULL;
    offset_ = RD_KAFKA_OFFSET_BEGINNING;
    //int32_t           partition;
	*/
    int run = 1;
    //initKafka();
}

KafkaConsumer::~KafkaConsumer()
{
	/*此调用将会阻塞，直到consumer撤销其分配，调用rebalance_cb(如果已设置)，
	commit offset到broker,并离开consumer group
	最大阻塞时间被设置为session.timeout.ms
	*/
	rd_kafka_resp_err_t err;

	err = rd_kafka_consumer_close(rk);
	if (err) {
		fprintf(stderr, "%% Failed to close consumer: %s\n", rd_kafka_err2str(err));
	}
	else {
		fprintf(stderr, "%% Consumer closed\n");
	}

    //释放topics list使用的所有资源和它自己  
    rd_kafka_topic_partition_list_destroy(topics_list);

    //destroy kafka handle  
    rd_kafka_destroy(rk);

    run = 5;
    //等待所有rd_kafka_t对象销毁，所有kafka对象被销毁，返回0，超时返回-1  
    while (run-- > 0 && rd_kafka_wait_destroyed(1000) == -1){
        printf("Waiting for librdkafka to decommission\n");
    }
    if (run <= 0){
        //dump rdkafka内部状态到stdout流  
        rd_kafka_dump(stdout, rk);
    }
}


void KafkaConsumer::msg_consume(rd_kafka_message_t *rkmessage,
    void *opaque) {
    if (rkmessage->err) {

        if (rkmessage->err == RD_KAFKA_RESP_ERR__UNKNOWN_PARTITION ||
            rkmessage->err == RD_KAFKA_RESP_ERR__UNKNOWN_TOPIC)
            run = 0;
        return;
    }

    if (rkmessage->key_len) {
        printf("Key: %.*s\n",
            (int)rkmessage->key_len, (char *)rkmessage->key);
    }
    /*
    printf("%.*s\n",
        (int)rkmessage->len, (char *)rkmessage->payload);
    */
    return;
}

/*
init all configuration of kafka
*/
bool KafkaConsumer::initKafka()
{
    string brokers = KafkaConsumer::brokers;
    const char *group = KafkaConsumer::groupid.c_str();
    const char *topic = KafkaConsumer::topics.c_str();



    // Kafka configuration 
    conf = rd_kafka_conf_new();

    //quick termination  
    //snprintf(tmp, sizeof(tmp), "%i", SIGIO);
    rd_kafka_conf_set(conf, "internal.termination.signal", tmp, NULL, 0);
    
    //topic configuration  
    topic_conf = rd_kafka_topic_conf_new();

    // Consumer groups require a group id 
    if (!group)
        group = "rdkafka_consumer_example";
    if (rd_kafka_conf_set(conf, "group.id", group,
        errstr, sizeof(errstr)) !=
        RD_KAFKA_CONF_OK) {
        fprintf(stderr, "%% %s\n", errstr);
        return FALSE;
    }

    //* Consumer groups always use broker based offset storage 
    if (rd_kafka_topic_conf_set(topic_conf, "offset.store.method",
        "broker",
        errstr, sizeof(errstr)) !=
        RD_KAFKA_CONF_OK) {
        fprintf(stderr, "%% %s\n", errstr);
        return FALSE;
    }
    /*
    if (rd_kafka_topic_conf_set(topic_conf, "auto.offest.reset",
        "smallest",//largest
        errstr, sizeof(errstr)) !=
        RD_KAFKA_CONF_OK) {
        fprintf(stderr, "%% %s\n", errstr);
        return FALSE;
    }
*/
    //* Set default topic config for pattern-matched topics. 
    rd_kafka_conf_set_default_topic_conf(conf, topic_conf);
    

    //实例化一个顶级对象rd_kafka_t作为基础容器，提供全局配置和共享状态  
    rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
    if (!rk){
        fprintf(stderr, "%% Failed to create new consumer:%s\n", errstr);
        return FALSE;
    }
    /* Create topic */
    rkt = rd_kafka_topic_new(rk, topic, topic_conf);

    //Librdkafka需要至少一个brokers的初始化list  
    int found;
    while ((found = brokers.find(";")) != string::npos)
    {
        string broker = brokers.substr(0, found);
        brokers = brokers.substr(found+1);
        if (rd_kafka_brokers_add(rk, broker.c_str()) == 0)
            fprintf(stderr, "%% No valid brokers specified\n");
    }
    if (rd_kafka_brokers_add(rk, brokers.c_str()) == 0)
        fprintf(stderr, "%% No valid brokers specified\n");


    //重定向 rd_kafka_poll()队列到consumer_poll()队列  
    rd_kafka_poll_set_consumer(rk);

    //创建一个Topic+Partition的存储空间(list/vector)  
    topics_list = rd_kafka_topic_partition_list_new(1);
    //把Topic+Partition加入list  
    rd_kafka_topic_partition_list_add(topics_list, topic,-1);//最后一个是订阅的partition
    //开启consumer订阅，匹配的topic将被添加到订阅列表中  
    //rd_kafka_assign  //分配方式
    //rd_kafka_subscribe //订阅方式
        
    if ((err = rd_kafka_subscribe(rk, topics_list))){
        fprintf(stderr, "%% Failed to start consuming topics: %s\n", rd_kafka_err2str(err));
        return FALSE;
    }
    /*
    if ((err = rd_kafka_assign(rk, topics_list))){
        fprintf(stderr, "%% Failed to start consuming topics: %s\n", rd_kafka_err2str(err));
        return FALSE;
    }*/
    return TRUE;
}

bool KafkaConsumer::consume_clear()
{
    run = 1;
    
    while (run){
        rd_kafka_message_t *rkmessage;
        rkmessage = rd_kafka_consumer_poll(rk, 200);
        if (rkmessage){

            int64_t seek_offset = RD_KAFKA_OFFSET_END;
            err = rd_kafka_seek(rkt, 0, seek_offset,
                2000);
            if (err)
                printf("Seek failed: %s\n",
                rd_kafka_err2str(err));

            break;
            
            msg_consume(rkmessage, NULL);
        }
    }
    return 0;
}

string KafkaConsumer::consume()
{
    run = 1;
	string message;
    while (run){
        rd_kafka_message_t *rkmessage;
        rkmessage = rd_kafka_consumer_poll(rk, 300);
        if (rkmessage){ 
            if (((rkmessage->payload)!=NULL)&&(rkmessage->err == RD_KAFKA_RESP_ERR_NO_ERROR))
            {
                message = (char *)rkmessage->payload;
            }
            rd_kafka_message_destroy(rkmessage);
			run = 0;//一次只取一条
        }
    }

    return message;
}

