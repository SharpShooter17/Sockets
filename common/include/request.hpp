#ifndef REQUEST_HPP
#define REQUEST_HPP

class Request {
	private:
	unsigned int m_request_code;
	unsigned int m_request_id;
	
	public:
	Request(unsigned int);

	unsigned int getRequestCode();
	void setRequestCode(unsigned int);

	unsigned int getRequestId();
	void setRequestId(unsigned int);
};

static unsigned int m_request_id_counter = 0;
unsigned int nextRequest();
#endif
