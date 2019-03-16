//! @file     NetworkFTPCodes.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// The FTP Codes
//----------------------------------------------------------------------------

// http://webdrive.com/support/titanftp/v10/webhelp/ftp_return_codes.htm
enum _NETWORK_FTP_CODE
{
	// 500 Series (The command was not accepted and the requested action did not take place).
	_FTP_CODE_SYNTAX_ERROR						= 500, //! Syntax error, command unrecognized. This may include errors such as command line too long.
	_FTP_CODE_SYNTAX_ERROR_IN_PARS				= 501, //! Syntax error in parameters or arguments.
	_FTP_CODE_COMMAND_NOT_IMPL					= 502, //! Command not implemented.
	_FTP_CODE_BAD_COMMANDS						= 503, //! Bad sequence of commands.
	_FTP_CODE_COMMAND_NOT_IMPL_FOR_PAR			= 504, //! Command not implemented for that parameter.
	_FTP_CODE_NOT_LOGGED_IN						= 530, //! Not logged in.
	_FTP_CODE_NEED_ACCOUNT_FOR_STORING_FILES	= 532, //! Need account for storing files.
	_FTP_CODE_FILE_UNAVAILABLE					= 550, //! Requested action not taken. File unavailable (For example, file not found, no access).
	_FTP_CODE_PAGE_TYPE_UNKNOWN					= 551, //! Requested action aborted. Page type unknown.
	_FTP_CODE_EXCEEDED_STORAGE_ALLOCATION		= 552, //! Requested file action aborted. Exceeded storage allocation (for current directory or dataset).
	_FTP_CODE_FILE_NAME_NOT_ALLOWED				= 553, //! Requested action not taken. File name not allowed.

	// 400 Series (The command was not accepted and the requested action did not take place, but the error condition is temporary and the action may be requested again).
	_FTP_CODE_SERVICE_NOT_AVAILABLE				= 421, //! Service not available, closing control connection. This may be a reply to any command if the service knows it must shut down.
	_FTP_CODE_CAN_NOT_OPEN_DATA_CONNECTION		= 425, //! Cannot open data connection.
	_FTP_CODE_CONNECTION_CLOSED					= 426, //! Connection closed; transfer aborted.
	_FTP_CODE_ACTION_NOT_TAKEN					= 450, //! Requested file action not taken.
	_FTP_CODE_LOCAL_ERROR						= 451, //! Requested action aborted. Local error in processing.
	_FTP_CODE_INSUFFICIENT_STORAGE_SPACE		= 452, //! Requested action not taken. Insufficient storage space in system. File unavailable (For example, file busy).

	// 300 Series (The command has been accepted, but the requested action is dormant, pending receipt of further information).
	_FTP_CODE_USER_NAME_OKAY					= 331, //! User name okay, need password.
	_FTP_CODE_NEED_ACCOUNT_FOR_LOGIN			= 332, //! Need account for login.
	_FTP_CODE_PENDING_FURTHER_INFO				= 350, //! Requested file action pending further information.

	// 200 Series (The requested action has been successfully completed).
	_FTP_CODE_COMAND_OKAY						= 200, //! Command okay.
	_FTP_CODE_SUPERFLUOUS_AT_THIS_SITE			= 202, //! Command not implemented, superfluous at this site.
	_FTP_CODE_SYSTEM_STATUS						= 211, //! System status, or system help reply.
	_FTP_CODE_DIRECTORY_STATUS					= 212, //! Directory status.
	_FTP_CODE_FILE_STATUS						= 213, //! File status.
	_FTP_CODE_HELP_MESSAGE						= 214, //! Help message. On how to use the server or the meaning of a particular non-standard command. This reply is useful only to the human user.
	_FTP_CODE_NAME_SYSTEM_TYPE					= 215, //! NAME system type. Where NAME is an official system name from the list in the Assigned Numbers document.
	_FTP_CODE_SERVICE_READY_FOR_NEW_USER		= 220, //! Service ready for new user.
	_FTP_CODE_SERVICE_CLOSING					= 221, //! Service closing control connection.
	_FTP_CODE_DATA_CONNECTION_OPEN				= 225, //! Data connection open; no transfer in progress.
	_FTP_CODE_CLOSING_DATA_CONNECTION			= 226, //! Closing data connection. Requested file action successful (for example: file transfer, file abort).
	_FTP_CODE_ENTERING_PASSIVE_MODE				= 227, //! Entering Passive Mode (h1,h2,h3,h4,p1,p2).
	_FTP_CODE_USER_LOGGED_IN					= 230, //! User logged in, proceed. Logged out if appropriate.
	_FTP_CODE_REQUESTED_FILE_ACTION_OKAY		= 250, //! Requested file action okay, completed.
	_FTP_CODE_PATHNAME_CREATED					= 257, //! PATHNAME created.

	// 100 Series (The requested action is being initiated, expect another reply before proceeding with a new command).
	_FTP_CODE_RESTART_MARKER_REPLY				= 110, //! Restart marker reply. In this case, the text is exact and not left to the particular implementation; it must read: MARK yyyy = mmmm (yyyy is user-process data stream marker, and mmmm server's equivalent marker. Note the spaces between markers and =).
	_FTP_CODE_SERVICE_READY_IN_MINUTES			= 120, //! Service ready in nnn minutes.
	_FTP_CODE_DATA_CONNECTION_ALREADY_OPEN		= 125, //! Data connection already open; transfer starting.
	_FTP_CODE_FILE_STATUS_OKAY					= 150, //! File status okay; about to open data connection.
};

}