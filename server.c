#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

int main(char **argv, int argc) {
	/*Server Handler*/
	uv_tcp_t *server = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
	struct sockaddr_in *bind_addr;

	/*Init*/
	uv_tcp_init(uv_default_loop(), server);

	/*address*/
        int rc = uv_ip4_addr("127.0.0.1", 12345, bind_addr);

	/* Socket Bind*/
	uv_tcp_bind(server,(const struct sockaddr*)bind_addr, 0);
}
