#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

uv_tcp_t *accept_client;
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

void close_cb(uv_handle_t *handle) {
	/*TODO check where to free mem of the handlers*/
}

void accept_callback(uv_stream_t *server, int status) {
	 if (status < 0) {
		 /*Error on the new connection*/
		 uv_close((uv_handle_t *)server, close_cb);
	 }
	 else if (status == 0) {
		 /*Success*/
		 accept_client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));

		 uv_tcp_init(uv_default_loop(), accept_client);
		 /*server and accept_client handles run on same loop*/

		 int rc = uv_accept(server, (uv_stream_t *)accept_client);
		 if (rc < 0) {
			 /*Error*/
			 uv_close((uv_handle_t *)accept_client, close_cb);
		 }
		 printf("Accepting connection\n");

		 uv_read_start((uv_stream_t *)accept_client,
				 allocate_buffer,
				 read_cb);
	 }
}

int main(char **argv, int argc) {
	/*Server Handler*/
	uv_tcp_t *server = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));

	struct sockaddr_in bind_addr;
	int rc;

	/*Init*/
	uv_tcp_init(uv_default_loop(), server);

	/*address*/
        rc = uv_ip4_addr("127.0.0.1", 12345, &bind_addr);

	/* Socket Bind*/
	uv_tcp_bind(server,(const struct sockaddr*)&bind_addr, 0);

	/*Socket Listen*/
	uv_listen((uv_stream_t *)server, 10/*backlog*/, accept_callback);

	/*Socket Accept*/

	/*Read*/
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}
