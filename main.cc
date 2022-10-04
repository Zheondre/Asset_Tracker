/*
Dev
Zheondre Calcano

About

Notes
on windows compile with g++ -std=17 main.cc -lwock32

References 

Http request 
https://stackoverflow.com/questions/1011339/how-do-you-make-a-http-request-with-c	

Json formatter
https://github.com/nlohmann/json
or 
https://github.com/Tencent/rapidjson/

*/


#include <iostream>
#include <fstream>

#include <memory>
#include <mutex>
#include <thread>
#include <chrono>

#include <vector> 
#include <utility>
#include <unordered_map>
#include <string.h>

#include <winsock2.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib") // what does this do ? 

enum status{ ABOVE, BELOW, EQUAL} ;

class alert{ 
	std::string assetName; 
	std::string price; 
	status level;
};

class asset { 

	mutable std::mutex _mtx;

	std::string name, price, date, mkcp; 
 	
	//or use a que 
	std::vector< std::pair< std::string, std::string>> history;
		
	public: 
	
	asset(): name(""), price(""), mkcp(""){} 
	
	asset(std::string nme, std::string prce, std::string mkp){ 
		name = nme; 
		price = prce; 

		mkcp = mkp;
	} 
	
	void setPrice(const std::string &p){ 
		std::lock_guard<std::mutex> l(_mtx);
	  	price = p;
	}; 
	void setMarketCap(const std::string &p){
		std::lock_guard<std::mutex> l(_mtx);
		mkcp = p;
	}; 
	std::string	getMarketCap(){
		std::lock_guard<std::mutex> l(_mtx);
		return mkcp;
	};
	std::string	getPrice(){
		std::lock_guard<std::mutex> l(_mtx);
		return price;
	}; 
	std::string	getName(){
		std::lock_guard<std::mutex> l(_mtx);
		return name;
	};
};

class tracker{ 

	std::unordered_map<std::string, std::shared_ptr<asset>> assets; 
	std::unordered_map<std::string, std::shared_ptr<asset>> favs;

	// might need to use a different socket library ?
	WSADATA wsaData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	struct hostent *host;

	//inline static const std::string get_request = "GET / HTTPS/1.1\r\nHost: ";
	inline static const std::string get_request = "GET https://";
	//inline static const std::string site = "https://api.coingecko.com";
	inline static const std::string site = "api.coingecko.com";
	inline static const std::string query = "/api/v3/simple/price?ids=";
	//inline static const std::string qtail  = "\r\n\r\n";

	std::string querycoinList;
	std::string currency; 
	std::string strQry;
 
	inline static int tokenCnt;
	//https port 443, http port 80 
	inline static const int port = 443; 
	inline static const int BUF_SZE = 1000;
	inline static char buffer[BUF_SZE];

	public: 
	// range

	tracker(): favs(), assets(){
		assets["bitcoin"] = std::make_shared<asset>("bitcoin", "0", "0"); 
		assets["ripple"] = std::make_shared<asset>("ripple", "0", "0"); 
		assets["solana"] = std::make_shared<asset>("solana", "0", "0"); 
		assets["ethereum"] = std::make_shared<asset>("ethereum", "0", "0");

		tokenCnt = 4;
		querycoinList = "bitcoin%2Cethereum%2Cripple%2Csolana"; 
		currency = "&vs_currencies=usd"; 

		strQry = get_request + site + query + querycoinList + currency;
		std::cout << "tracker constructer completed" <<std::endl;
	}
	
	~tracker(){
		closesocket(Socket);
    	WSACleanup();
	}

	bool AddAsset(const std::string & asst);

	int web();

	void updateAssets();
	void printAssets(); 
};

int tracker::web(){ 

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        std::cout << "WSAStartup failed.\n";
        system("pause");
        return 1;
    }

	Socket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	host = gethostbyname(site.c_str()); 

	SockAddr.sin_port=htons(port);
	SockAddr.sin_family=AF_INET;
	if(!host){ 
		std::cout << "Error: Host is null" << std::endl; 
		return 1; 
	}
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);


	if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
		std::cout << "Could not connect";
		system("pause");
		return 1;
	}

	return 0;
}

void tracker::printAssets(){ 

	for(;;){
		std::cout << "\n"; 
		for(auto& it : assets){ 
			std::cout << it.second->getName() << " " << it.second->getPrice() << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
} 

void tracker::updateAssets(){ 

	for(;;){
		try{ 
			std::cout << "\n Sending Request\n";
			std::cout << "qs: " << strQry << std::endl;
			// send GET / HTTP
			send(Socket, strQry.c_str(), strlen(strQry.c_str()), 0);

			//use a json serializer 
			// recieve html
			int nDataLength =0;
			while ((nDataLength = recv(Socket, buffer, BUF_SZE, 0)) > 0){        
				//std::cout << nDataLength << std::endl;
				int i = 0;
				while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r'){

					//website_HTML+=buffer[i];
					std::cout << buffer[i];
					i += 1;
				}               
			}
			std::cout << nDataLength << std::endl;
			if(nDataLength < 0){ 
				std::cout << WSAGetLastError() << std::endl;
			}

			//TEST TEST TEST 
			std::cout << "\n<--- Leaving Update Asset" << std::endl;
			return; 
			//TEST TEST TEST
			#if 0		
			for(std::string &coin: assets) { 

				switch(coin.GetName()){ 
					case: "BTC": 
						/*request 
						std::string request
						coin.setPrice(request)

						*/
					break; 
					case: "ETH":
					break;  
					case: "XRP":
					break;
					case "SOL":
					break;
					default: 
				}
			}
			#endif 
		}catch(...){ 
			std::cout << "Connection Error, retrying.." << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

}

class Stats { 

	int avgPrice; 
	int low; 
	int high; 
	
	//static findav(){ 
	//}

} ;

int main(){ 

	tracker t; 

	if(t.web()) 
		return 0 ; 

	std::thread t1(tracker::updateAssets, t); 
	//std::thread t2(tracker::printAssets, t); 

	t1.join(); 
	//t2.join(); 

	return 0;
} 