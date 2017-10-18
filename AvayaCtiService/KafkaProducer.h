#ifndef __PRODUCER_H__  
#define __PRODUCER_H__  
#include <string>  
#include <csignal>  
#include <iostream>  
#include <stdlib.h>  
#include <stdio.h>
#include <signal.h>   
#include "iostream"
#include <fstream>
#include "rdkafka.h"  
#include "rdkafkacpp.h"  

using namespace std;

#define FALSE         0
#define TRUE          1
class KafkaProducer{
public:
	KafkaProducer(const string& brokers, const string& topics/*, int32_t partition*/);
	KafkaProducer();
	virtual ~KafkaProducer();
	/*
	每条消息调用一次该回调函数，说明消息是传递成功(rkmessage->err == RD_KAFKA_RESP_ERR_NO_ERROR)
	还是传递失败(rkmessage->err != RD_KAFKA_RESP_ERR_NO_ERROR)
	该回调函数由rd_kafka_poll()触发，在应用程序的线程上执行
	*/
	//void dr_msg_cb(rd_kafka_t *rk, const rd_kafka_message_t *rkmessage, void *opaque);//回调函数
	bool PutBrokers(string);
	bool PutTopics(string);

	bool initKafka();
	bool initKafka(void(*dr_msg_cb)(rd_kafka_t *rk, const rd_kafka_message_t *rkmessage, void *opaque));
	bool produce(string& mes, int32_t partition);//运行生产者 ,向CI的指定分区生产mes
	//bool produce();
private:
	rd_kafka_t *rk;            /*Producer instance handle*/
	rd_kafka_topic_t *rkt;     /*topic对象*/
	rd_kafka_conf_t *conf;    
	char errstr[512];
	string brokers;
	string topics;
	//int32_t partition;
	int run = 1;  
};
#endif
