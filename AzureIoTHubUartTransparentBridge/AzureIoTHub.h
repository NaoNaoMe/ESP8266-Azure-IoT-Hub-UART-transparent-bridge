#ifndef AzureIoTHub_h
#define AzureIoTHub_h

#include <PubSubClient.h>

struct CloudConfig {
	unsigned int sasExpiryDate = 1737504000;  // Expires Wed, 22 Jan 2025 00:00:00 GMT
	const char *host;
	char *key;
	const char *id;
	const char* fullSas;
	const char * postUrl;
	const char * hubUser;
	const char * getUrl;
};

typedef void(*CallBackFunction) (uint8_t* receiveData, unsigned int dataLength);

class AzureIoTHub {
  public:
    CloudConfig authentication();
  	bool connect();
  	void run();
    void push(byte* sendData, unsigned int dataLength);
  	void begin(String cs);
  	void setCallback(CallBackFunction _cbFunc);
  private:
  	static CallBackFunction cbFunc;
  	static void callback(char* topic, byte* payload, unsigned int length);
  	const char *GetStringValue(String value);
  	String splitStringByIndex(String data, char separator, int index);
  	String urlEncode(const char* msg);
  	String createIotHubSas(char *key, String url);
};

#endif
