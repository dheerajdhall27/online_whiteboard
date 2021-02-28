/**
*  @file   ClientMessageType.hpp
*  @brief  Enum variables for classifying client's messages
*  @author Mike and van_doesnt_go
*  @date    2020 - 04 - 05
***********************************************/

#ifndef APP_CLIENTMESSAGETYPE_HPP
#define APP_CLIENTMESSAGETYPE_HPP

/*! \brief Enum variables for classifying client's messages
 */
enum ClientMessageType {
    CLIENT_JOINING,
    DRAW_INFORMATION,
    UNDO_COMMAND,
    REDO_COMMAND,
    IS_CLIENT_ALIVE,
    PAINT_CANVAS
};

#endif //APP_CLIENTMESSAGETYPE_HPP
