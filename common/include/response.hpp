#pragma once

class Response {
	private:
	unsigned int m_response_code;
	unsigned int m_request_id;

	public:
	Response(unsigned int, unsigned int):
	unsigned int getResponseCode();
	void setRequestCode(unsigned int);

	unsigned int getRequestId();
	void setRequestId(unsigned int);
};
