/*
 Copyright (c) 2015 Mathieu Laurendeau <mat.lau@laposte.net>
 License: GPLv3
 */

#ifndef PROXY_H_
#define PROXY_H_

int proxy_init(char * path);
int proxy_start(char * port, char * plugin_path, char * plugin_name);
int plugin_init(char * plugin_path, char *plugin);
void proxy_stop();

#endif /* PROXY_H_ */
