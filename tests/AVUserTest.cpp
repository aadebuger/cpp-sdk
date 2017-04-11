#define BOOST_TEST_MODULE AVUser 1.0 Test
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "AVOSCloud.h"
#include "User/AVUser.h"

using namespace std;
using namespace avoscloud;

//#error replace szoGzmrv3vCog9IaAlMwvPdu-gzGzoHsz and RkW3UjoK2br9q15ejFsPJFCN with real appId and appKey

BOOST_AUTO_TEST_CASE(AVUser_SignUp_Test) {
  AVOSCloud::setApplicationId("szoGzmrv3vCog9IaAlMwvPdu-gzGzoHsz", "RkW3UjoK2br9q15ejFsPJFCN");

  AVUser* user = AVUser::user();
  user->username = "cyang123321";
  user->password = "123456";
  user->email = "cyang123321@avoscloud.com";

  user->signUp();

  BOOST_CHECK(user->isAuthenticated());

  user->deleteInBackground();
  user->release();
}

BOOST_AUTO_TEST_CASE(AVUser_Login_Test) {
  AVOSCloud::setApplicationId("szoGzmrv3vCog9IaAlMwvPdu-gzGzoHsz", "RkW3UjoK2br9q15ejFsPJFCN");

  AVUser* user = AVUser::user();
  user->username = "cyang123321";
  user->password = "123456";
  user->email = "cyang123321@avoscloud.com";
  user->signUp();
  AVUser::logOut();

  AVUser::loginWithUsernameAndPassword("cyang123321", "123456");
  BOOST_CHECK(AVUser::currentUser() != nullptr && AVUser::currentUser()->isAuthenticated());

  AVUser::currentUser()->deleteInBackground();

  user->release();
}

BOOST_AUTO_TEST_CASE(AVUser_UpdatePassword_Test) {
  AVOSCloud::setApplicationId("szoGzmrv3vCog9IaAlMwvPdu-gzGzoHsz", "RkW3UjoK2br9q15ejFsPJFCN");

  AVUser* user = AVUser::user();
  user->username = "cyang123321";
  user->password = "123456";
  user->email = "cyang123321@avoscloud.com";
  user->signUp();

  user->updatePasswordWithCallback("123456", "654321", [&](Json::Value const & root, AVError const & error){
      //do nothing
    });

  AVUser::logOut();

  AVUser::loginWithUsernameAndPassword("cyang123321", "654321");
  BOOST_CHECK(AVUser::currentUser() != nullptr && AVUser::currentUser()->isAuthenticated());

  AVUser::currentUser()->deleteInBackground();

  user->release();
}

BOOST_AUTO_TEST_CASE(AVUser_RequestPasswordResetForEmail_Test) {
  AVOSCloud::setApplicationId("szoGzmrv3vCog9IaAlMwvPdu-gzGzoHsz", "RkW3UjoK2br9q15ejFsPJFCN");

  AVUser* user = AVUser::user();
  user->username = "cyang123321";
  user->password = "123456";
  user->email = "cyang@avoscloud.com";
  user->signUp();

  BOOST_CHECK(AVUser::currentUser() != nullptr && AVUser::currentUser()->isAuthenticated());

  AVUser::requestPasswordResetForEmail("cyang@avoscloud.com");

  user->deleteInBackground();

  user->release();
}
