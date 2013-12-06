/**
* Copyright (C) 2013 kangliqiang ,kangliq@163.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#if!defined __CONSUMEMESSAGECONCURRENTLYSERVICE_H__
#define __CONSUMEMESSAGECONCURRENTLYSERVICE_H__

#include "ConsumeMessageService.h"

#include <list>
#include <string>

#include "MessageQueueLock.h"
#include "ConsumerStatManage.h"
#include "MessageExt.h"
#include "MessageListener.h"

class DefaultMQPushConsumerImpl;
class DefaultMQPushConsumer;
class MessageListenerConcurrently;


/**
* ����������Ϣ����
* 
*/
class ConsumeMessageConcurrentlyService : public ConsumeMessageService
{
public:
	ConsumeMessageConcurrentlyService(DefaultMQPushConsumerImpl* pDefaultMQPushConsumerImpl,
		MessageListenerConcurrently* pMessageListener);

	void start();
	void shutdown();
	ConsumerStat getConsumerStat();
	bool sendMessageBack(MessageExt& msg, ConsumeConcurrentlyContext& context);

	/**
	* ��Consumer���ض�ʱ�߳��ж�ʱ����
	*/
	void submitConsumeRequestLater(std::list<MessageExt>& msgs,
		ProcessQueue& processQueue,
		MessageQueue& messageQueue);

	void submitConsumeRequest(std::list<MessageExt*>& msgs,
		ProcessQueue& processQueue,
		MessageQueue& messageQueue,
		bool dispathToConsume);

	void updateCorePoolSize(int corePoolSize);

private:
	DefaultMQPushConsumerImpl* m_pDefaultMQPushConsumerImpl;
	DefaultMQPushConsumer* m_pDefaultMQPushConsumer;
	MessageListenerConcurrently* m_pMessageListener;
	std::string m_consumerGroup;
};

#endif
