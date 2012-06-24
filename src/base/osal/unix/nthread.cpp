// LICENSE: (Please see the file COPYING for details)
//
// NUS - Nemesis Utilities System: A C++ application development framework 
// Copyright (C) 2006, 2007 Otavio Rodolfo Piske
//
//  This file is part of NUS
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation version 2.1
//  of the License.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
#include "nthread.h"


void *nthread_start_routine(void *data) { 
	NThread *thread = static_cast<NThread *>(data);
	
	thread->threadStart();

	return NULL;
}

NThread::NThread(void)
	: NObject()
{

}


void NThread::threadCreate() {
	int ret = 0; 
	pthread_t a_thread;

	ret = pthread_create(&a_thread, NULL, nthread_start_routine, (void *) this);
	
}
