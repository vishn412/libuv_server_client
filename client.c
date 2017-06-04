#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

void connect_callback(uv_connect_t* conn_req, int status) {

	int rc = status;
	if (rc < 0) {
		/*Fail*/
	}
	printf("Connection Established\n");
}

int main(char **argv, int argc) {
	/*Client Handler*/
	uv_tcp_t *client = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));

	uv_connect_t *connect = (uv_connect_t *)malloc(sizeof(uv_connect_t));

	struct sockaddr_in peer_addr;
	int rc;

	rc = uv_tcp_init(uv_default_loop(), client);

	if(rc) {
		printf("Error\n");
	}

	uv_ip4_addr("127.0.0.1", 12345, &peer_addr);

	rc = uv_tcp_connect(connect, client, (const struct sockaddr *)&peer_addr , connect_callback);

	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}
