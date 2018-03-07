#ifndef __HttpServer_H__
#define __HttpServer_H__

#include <Arduino.h>

#ifdef MDUINO_PLUS
#include <Ethernet2.h>
#else
#include <Ethernet.h>
#endif

typedef struct {
	String method;
	String route;
	String queryString;
	String body;
} HttpRequest;

class HttpResponse {
	public:
		explicit HttpResponse(EthernetClient &client);

	public:
		bool send(const String &body, const String &contentType, uint16_t status, const String &statusText);
		bool send(const String &body, const String &contentType) {
			return send(body, contentType, 200, "OK");
		}

		inline bool text(const String &body) {
			return send(body, "text/plain");
		}
		inline bool text(const String &body, uint16_t status, const String &statusText) {
			return send(body, "text/plain", status, statusText);
		}

		inline bool html(const String &body) {
			return send(body, "text/html");
		}
		inline bool html(const String &body, uint16_t status, const String &statusText) {
			return send(body, "text/html", status, statusText);
		}

		bool redirect(const String &dest);

	private:
		EthernetClient &_client;
};

class HttpServer : public EthernetServer {
	private:
		enum ParseSections {
			MethodSection,
			PathSection,
			QueryStringSection,
			VersionSection,
			HeaderNameSection,
			HeaderValueSection,
			EmptyLineSection,
			BodySection,
			FinishedSection,
		};

	public:
		explicit HttpServer(uint16_t port = 80);

	public:
		void update();
};

#endif // __HttpServer_H__