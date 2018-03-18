#ifndef REQUEST_HPP
#define REQUEST_HPP

class Request {
	private:
	union 
	{ 
		unsigned int m_request_code;
		unsigned char codeCh[4];
	};
	
	unsigned int m_request_id;
	
	public:
	Request();
	Request(unsigned int);

	unsigned int getRequestCode();
	void setRequestCode(unsigned int);

	unsigned int getRequestId();
	void setRequestId(unsigned int);
	
	unsigned char* getCodeCh() { return this->codeCh; }
};

static unsigned int m_request_id_counter = 0;
unsigned int nextRequest();
#endif
