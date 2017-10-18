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
	ÿ����Ϣ����һ�θûص�������˵����Ϣ�Ǵ��ݳɹ�(rkmessage->err == RD_KAFKA_RESP_ERR_NO_ERROR)
	���Ǵ���ʧ��(rkmessage->err != RD_KAFKA_RESP_ERR_NO_ERROR)
	�ûص�������rd_kafka_poll()��������Ӧ�ó�����߳���ִ��
	*/
	//void dr_msg_cb(rd_kafka_t *rk, const rd_kafka_message_t *rkmessage, void *opaque);//�ص�����
	bool PutBrokers(string);
	bool PutTopics(string);

	bool initKafka();
	bool initKafka(void(*dr_msg_cb)(rd_kafka_t *rk, const rd_kafka_message_t *rkmessage, void *opaque));
	bool produce(string& mes, int32_t partition);//���������� ,��CI��ָ����������mes
	//bool produce();
private:
	rd_kafka_t *rk;            /*Producer instance handle*/
	rd_kafka_topic_t *rkt;     /*topic����*/
	rd_kafka_conf_t *conf;    
	char errstr[512];
	string brokers;
	string topics;
	//int32_t partition;
	int run = 1;  
};
#endif
