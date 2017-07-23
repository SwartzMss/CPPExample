/*
 * Copyright (c) 2000-2007 Niels Provos <provos@citi.umich.edu>
 * Copyright (c) 2007-2012 Niels Provos and Nick Mathewson
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _EVENT2_EVENT_STRUCT_H_
#define _EVENT2_EVENT_STRUCT_H_

/** @file event2/event_struct.h

  Structures used by event.h.  Using these structures directly WILL harm
  forward compatibility: be careful.

  No field declared in this file should be used directly in user code.  Except
  for historical reasons, these fields would not be exposed at all.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <event2/event-config.h>
#ifdef _EVENT_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef _EVENT_HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

/* For int types. */
#include <event2/util.h>

/* For evkeyvalq */
#include <event2/keyvalq_struct.h>

#define EVLIST_TIMEOUT	0x01
#define EVLIST_INSERTED	0x02
#define EVLIST_SIGNAL	0x04
#define EVLIST_ACTIVE	0x08
#define EVLIST_INTERNAL	0x10
#define EVLIST_INIT	0x80

/* EVLIST_X_ Private space: 0x1000-0xf000 */
#define EVLIST_ALL	(0xf000 | 0x9f)

/* Fix so that people don't have to run with <sys/queue.h> */
#ifndef TAILQ_ENTRY
#define _EVENT_DEFINED_TQENTRY
#define TAILQ_ENTRY(type)						\
struct {								\
	struct type *tqe_next;	/* next element */			\
	struct type **tqe_prev;	/* address of previous next element */	\
}
#endif /* !TAILQ_ENTRY */

#ifndef TAILQ_HEAD
#define _EVENT_DEFINED_TQHEAD
#define TAILQ_HEAD(name, type)			\
struct name {					\
	struct type *tqh_first;			\
	struct type **tqh_last;			\
}
#endif

struct event_base;
struct event {
	TAILQ_ENTRY(event) ev_active_next;//�������
	TAILQ_ENTRY(event) ev_next;//ע���¼�����
	/* for managing timeouts */
	union {
		TAILQ_ENTRY(event) ev_next_with_common_timeout;
		int min_heap_idx;//��־��event�ṹ���ڶ��е�λ��
	} ev_timeout_pos;//�����ڶ�ʱ�¼������� EV_TIMEOUT
	//����IO,���ļ�������(���)������signal ���ź�ֵ
	evutil_socket_t ev_fd;

	//������event_base
	struct event_base *ev_base;

	//��Ϊ�źź�IO�ǲ���ͬʱ���õģ����Կ���ʹ��union��ʡ�ڴ�
	union {
	//�������źŻ���IO,����һ��TAILQ_ENTRY�Ķ��У���������������
	//�û�����ͬһ��fd����event_new��Σ�����ʹ���˲�ͬ�Ļص�����
	//ÿ�ε���event_new�������һ��event*,��xxx_next��Ա���ǰ���Щevent����������
		/* ����IO�¼� */
		struct {
			TAILQ_ENTRY(event) ev_io_next;
			struct timeval ev_timeout;
		} ev_io;

		/* �����ź��¼� */
		struct {
			TAILQ_ENTRY(event) ev_signal_next;
			short ev_ncalls;//�¼�����ִ��ʱ������ev_callback�Ĵ���
			/* Allows deletes in callback */
			short *ev_pncalls;
		} ev_signal;
	} _ev;

	short ev_events;//��ע���¼����ͣ���������io�¼�(EV_WRITE��EV_READ)���ź�(EV_SIGNAL)�Ͷ�ʱ(EV_TIMEOUT) ����ѡ��EV_PERSISR ������һ�������¼�
	short ev_res;  //��¼�˵�ǰ�����¼�������
	short ev_flags; //������ǰ��״̬������ֵΪEVLIST_XXX
	ev_uint8_t ev_pri;	//���ȼ���ԽСԽ�ߣ�ͨ��event_priority_set����
	ev_uint8_t ev_closure;
	struct timeval ev_timeout;//���ڶ�ʱ�������ó�ʱʱ��

	/* allows us to adopt for different types of events */
	void (*ev_callback)(evutil_socket_t, short, void *arg);//�ص�����
	void *ev_arg;//�ص������Ĳ���
};

TAILQ_HEAD (event_list, event);

#ifdef _EVENT_DEFINED_TQENTRY
#undef TAILQ_ENTRY
#endif

#ifdef _EVENT_DEFINED_TQHEAD
#undef TAILQ_HEAD
#endif

#ifdef __cplusplus
}
#endif

#endif /* _EVENT2_EVENT_STRUCT_H_ */