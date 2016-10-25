// Copyright (c) 2016 The tourism Authors. All rights reserved.
// comm_head.h
// Created on: 2016年8月10日.
// Author: Paco.
#ifndef PUB_COMM_COMM_HEAD_H_
#define PUB_COMM_COMM_HEAD_H_

enum PACKET_TYPE {
  ERROR_TYPE = 0,
  USER_TYPE = 1,
  CHAT_TYPE = 2
};

enum PACKET_ERROR {
  SQL_EXEC_ERROR = -1000,
  USER_LOGIN_JSON_ERR = -1001,
  PHONE_NUM_ERR = -1002,
  PHONE_OR_PASSWD_ERR = -1003,
  NEARBY_GUIDE_JSON_ERR = -1004,
  NO_GUIDE_NEARBY = -1005,
  HEART_PACKET_JSON_ERR = -1006,
  NO_GUIDE = -1007,
  RECOMMEND_GUIDE_JSON_ERR = -1008,
  NO_RECOMMEND_GUIDE = -1009,
  ASK_INVITATION_JSON_ERR = -1010,
  CHANGE_PASSWD_JSON_ERR = -1011,
  USER_NOT_IN_CACHE = -1012,
  CHANGE_OLD_PWD_ERR = -1013,
  CHAT_PACKET_JSON_ERR = -1014,
  NEW_ORDER_ERR = -1015,
  CHAT_RECORD_JSON_ERR = -1016,
  NO_CHAT_RECORD = -1017,
  OBTAIN_VERIFYCODE_JSON_ERR = -1018,
  REGISTER_ACCOUNT_JSON_ERR = -1019,
  VERIFY_CODE_OVERDUE = -1020,
  VERIFY_CODE_ERR = -1021,
  IMPROVE_DATA_JSON_ERR = -1022,
  TRIP_RECORD_JSON_ERR = -1023,
  SERVICE_DETAILS_JSON_ERR = -1024,
  NO_USER = -1025,
  DRAW_BILL_JSON_ERR = -1026,
  NO_USER_DEVICE_TOKEN = -1027, //没有该用户devicetoken
  DEVICE_TOKEN_ERR = -1028,
  MSG_READ_JSON_ERR = -1029,
  EVALUATE_TRIP_JSON_ERR = -1030,
  ANSWER_INVITATION_JSON_ERR = -1031,
  ORDER_STATUS_ERR = -1032,
  BILL_RECORD_JSON_ERR = -1033,
  BLACK_PRIVILEGE_EMPTY = -1034,
  BLACKCARD_INFO_JSON_ERR = -1035,
  BLACKCARD_CONSUME_RECORD_JSON_ERR = -1036,
};


#endif  // PUB_COMM_COMM_HEAD_H_
