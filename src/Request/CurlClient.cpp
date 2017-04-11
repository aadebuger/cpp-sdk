//
//  CurlClient.cpp
//  AVOSCloud
//
//  Created by hua zhuang on 2/3/2017.
//
//

#include <string>
#include <strstream>
#include "CurlClient.hpp"

#include "curl_easy.h"
#include "curl_exception.h"
#include "curl_header.h"
using std::ostringstream;

using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
using curl::curl_ios;
using curl::curl_header;

CurlClient::http::client::client()
{
    
}
CurlClient::http::client::request::request(const std::string &url):url(url)

{
    headerv={};
}
void CurlClient::http::client::request::addHeader(const  std::string &key, const std::string &value)
{
    
    headerv.insert( std::pair<std::string,std::string>(key,value) );
    
}
CurlClient::http::client::response  CurlClient::http::client::post(CurlClient::http::client::request request , const std::string &poststr)
{
    
    
    // Let's declare a stream
    ostringstream str;
    curl_header header;
    
    // We are going to put the request's output in the previously declared stream
    curl_ios<ostringstream> ios(str);
    // Declaration of an easy object
    curl_easy easy(ios);
    
    //   header.add("Token: test");
    std::map<std::string,std::string> headerv = request.getHeaderv();
    for ( std::map<std::string,std::string>::iterator it = headerv.begin(); it !=  headerv .end(); ++it)
    {
        std::cout<< it->first<< "value="<<it->second<< std::endl;
        header.add( it->first +": "+ it->second);
        
    }
    header.add("Accept: application/json");
    header.add("Content-Type: application/json" );
    
    // Add some option to the curl_easy object.
    easy.add<CURLOPT_HTTPHEADER>(header.get());
    // "http://www.httpbin.org/post"
    
    easy.add<CURLOPT_URL>(request.getUrl().c_str());
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);
 //   easy.add<CURLOPT_HTTPPOST>( poststr );
   
    easy.add<CURLOPT_CUSTOMREQUEST>( "POST");
    easy.add<CURLOPT_POSTFIELDS>(poststr.c_str());
    easy.add<CURLOPT_SSL_VERIFYPEER>(0);
    
    
    try {
        // Execute the request.
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        curlcpp_traceback errors = error.get_traceback();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }
    
    // Retrieve information about curl current session.
    auto x = easy.get_info<CURLINFO_CONTENT_TYPE>();
    auto y = easy.get_info<CURLINFO_HTTP_CODE>();
    
    // Print out content type
    std::cout << x.get() << std::endl;
    
    std::cout<< str.str()<<std::endl;
    std::cout << y.get() << std::endl;
    
     CurlClient::http::client::response aresponse(str.str(),y.get());
    return aresponse;
 
}
CurlClient::http::client::response  CurlClient::http::client::put( CurlClient::http::client::request request , const std::string &poststr)
{
   
    // Let's declare a stream
    ostringstream str;
    curl_header header;
    
    // We are going to put the request's output in the previously declared stream
    curl_ios<ostringstream> ios(str);
    // Declaration of an easy object
    curl_easy easy(ios);
    
    //   header.add("Token: test");
    std::map<std::string,std::string> headerv = request.getHeaderv();
    for ( std::map<std::string,std::string>::iterator it = headerv.begin(); it !=  headerv .end(); ++it)
    {
        std::cout<< it->first<< "value="<<it->second<< std::endl;
        header.add( it->first +": "+ it->second);
        
    }
    header.add("Accept: application/json");
    header.add("Content-Type: application/json" );
    
    // Add some option to the curl_easy object.
    easy.add<CURLOPT_HTTPHEADER>(header.get());
  //  easy.add<CURLOPT_URL>("http://www.httpbin.org/post");
   
    easy.add<CURLOPT_URL>(request.getUrl().c_str());
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);
    //   easy.add<CURLOPT_HTTPPOST>( poststr );
    
    easy.add<CURLOPT_CUSTOMREQUEST>( "POST");
    easy.add<CURLOPT_POSTFIELDS>(poststr.c_str());
    easy.add<CURLOPT_SSL_VERIFYPEER>(0);
    
    try {
        // Execute the request.
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        curlcpp_traceback errors = error.get_traceback();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }
    
    // Retrieve information about curl current session.
    auto x = easy.get_info<CURLINFO_CONTENT_TYPE>();
    auto y = easy.get_info<CURLINFO_HTTP_CODE>();
    
    // Print out content type
    std::cout << x.get() << std::endl;
    
    std::cout<< str.str()<<std::endl;
    std::cout << y.get() << std::endl;
    
    CurlClient::http::client::response aresponse(str.str(),y.get());
    return aresponse;
}
CurlClient::http::client::response  CurlClient::http::client::get(CurlClient::http::client::request request )
{
    // Let's declare a stream
    ostringstream str;
    curl_header header;
    
    // We are going to put the request's output in the previously declared stream
    curl_ios<ostringstream> ios(str);
    // Declaration of an easy object
    curl_easy easy(ios);
    
 //   header.add("Token: test");
    std::map<std::string,std::string> headerv = request.getHeaderv();
    for ( std::map<std::string,std::string>::iterator it = headerv.begin(); it !=  headerv .end(); ++it)
    {
        std::cout<< it->first<< "value="<<it->second<< std::endl;
        header.add( it->first +": "+ it->second);
        
    }
    
    // Add some option to the curl_easy object.
    easy.add<CURLOPT_HTTPHEADER>(header.get());
   // easy.add<CURLOPT_URL>("http://www.httpbin.org/get");
        easy.add<CURLOPT_URL>(request.getUrl().c_str());
    
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);
    easy.add<CURLOPT_SSL_VERIFYPEER>(0);
    
    try {
        // Execute the request.
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        curlcpp_traceback errors = error.get_traceback();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }
    
    // Retrieve information about curl current session.
    auto x = easy.get_info<CURLINFO_CONTENT_TYPE>();
    auto y = easy.get_info<CURLINFO_HTTP_CODE>();
    
    // Print out content type
    std::cout << x.get() << std::endl;
    
    std::cout<< str.str()<<std::endl;
   std::cout << y.get() << std::endl;
    
    CurlClient::http::client::response aresponse(str.str(),y.get());
    return aresponse;
}
CurlClient::http::client::response  CurlClient::http::client::delete_(CurlClient::http::client::request  request)
{
    
    // Let's declare a stream
    ostringstream str;
    curl_header header;
    
    // We are going to put the request's output in the previously declared stream
    curl_ios<ostringstream> ios(str);
    // Declaration of an easy object
    curl_easy easy(ios);
    
    //   header.add("Token: test");
    std::map<std::string,std::string> headerv = request.getHeaderv();
    for ( std::map<std::string,std::string>::iterator it = headerv.begin(); it !=  headerv .end(); ++it)
    {
        std::cout<< it->first<< "value="<<it->second<< std::endl;
        header.add( it->first +": "+ it->second);
        
    }

    header.add("Accept: application/json");
    header.add("Content-Type: application/json" );
    
    
    // Add some option to the curl_easy object.
    easy.add<CURLOPT_HTTPHEADER>(header.get());
    //easy.add<CURLOPT_URL>("http://www.httpbin.org/get");
        easy.add<CURLOPT_URL>(request.getUrl().c_str());
    
    easy.add<CURLOPT_FOLLOWLOCATION>(1L);
    easy.add<CURLOPT_CUSTOMREQUEST>( "DELETE");
    easy.add<CURLOPT_SSL_VERIFYPEER>(0);
    
    try {
        // Execute the request.
        easy.perform();
    } catch (curl_easy_exception error) {
        // If you want to get the entire error stack we can do:
        curlcpp_traceback errors = error.get_traceback();
        // Otherwise we could print the stack like this:
        error.print_traceback();
        // Note that the printing the stack will erase it
    }
    
    // Retrieve information about curl current session.
    auto x = easy.get_info<CURLINFO_CONTENT_TYPE>();
    auto y = easy.get_info<CURLINFO_HTTP_CODE>();
    
    // Print out content type
    std::cout << x.get() << std::endl;
    
    std::cout<< str.str()<<std::endl;
    std::cout << y.get() << std::endl;
    
    CurlClient::http::client::response aresponse(str.str(),y.get());
    return aresponse;
    
}

