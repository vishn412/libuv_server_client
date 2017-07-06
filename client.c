#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

uv_tcp_t client;
uv_buf_t buffer;

void allocate_buffer(uv_handle_t *handle, size_t size, uv_buf_t *buf) {
        buffer.base = malloc(size);
        buffer.len = size;
        *buf = buffer;
}

void read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
        if (nread > 0) {
            printf("%s\n", buf);
            free(buf->base);
            buf = NULL;
        }
        else  {
            printf("ERROR TODO : print error no\n");
        }
}

void connect_callback(uv_connect_t* conn_req, int status) {

	int rc = status;
	if (rc < 0) {
		return;
		/*Fail*/
	}
	printf("Connection Established\n");

	uv_read_start((uv_stream_t * )&client,
		      allocate_buffer,
                      read_cb);
}

int main(char **argv, int argc) {
	/*Client Handler*/
	uv_connect_t connect;

	struct sockaddr_in peer_addr;
	int rc;
	printf("time to start loop\n");

	rc = uv_tcp_init(uv_default_loop(), &client);

	printf("started default loop\n");

	if(rc) {
	    printf("Error TODO print error num\n");
	}

	uv_ip4_addr("127.0.0.1", 12345, &peer_addr);

	printf("Time to connect\n");

	rc = uv_tcp_connect(&connect, &client, (const struct sockaddr *)&peer_addr , connect_callback);

	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}
