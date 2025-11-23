enum SceNotificationRequestType
{
	NotificationRequest = 0,
	SystemNotification = 1,
	SystemNotificationWithUserId = 2,
	SystemNotificationWithDeviceId = 3,
	SystemNotificationWithDeviceIdRelatedToUser = 4,
	SystemNotificationWithText = 5,
	SystemNotificationWithTextRelatedToUser = 6,
	SystemNotificationWithErrorCode = 7,
	SystemNotificationWithAppId = 8,
	SystemNotificationWithAppName = 9,
	SystemNotificationWithAppInfo = 9,
	SystemNotificationWithAppNameRelatedToUser = 10,
	SystemNotificationWithParams = 11,
	SendSystemNotificationWithUserName = 12,
	SystemNotificationWithUserNameInfo = 13,
	SendAddressingSystemNotification = 14,
	AddressingSystemNotificationWithDeviceId = 15,
	AddressingSystemNotificationWithUserName = 16,
	AddressingSystemNotificationWithUserId = 17,

	Debug = 100,
	TrcCheckNotificationRequest = 101,
	NpDebugNotificationRequest = 102,
	WebDebug = 102,
	UNK_103 = 103,
};

enum NotificationAPI
{
	ToastPopup = 0,
	NotifyDatabase = 1,
};

#pragma pack(push, 1)
struct SceNotificationRequest
{
	enum SceNotificationRequestType Type;   // 0x00
	uint32_t ReqId;            				// 0x04
	uint32_t Priority;						// 0x08
	uint32_t MsgId;            				// 0x0C
	uint32_t TargetId;						// 0x10
	uint32_t UserId;						// 0x14
	uint32_t unk_18;						// 0x18
	uint32_t unk_1C;						// 0x1C
	uint32_t AppId;            				// 0x20
	uint32_t ErrorNumber;					// 0x24
	uint32_t Attribute;						// 0x28
	uint8_t  HasIcon;						// 0x2C
	union
	{
		struct
		{
			char Message[0x400];			// 0x2D
			char IconImageUri[0x800];		// 0x42D
		};

		struct
		{
			char unk1[180];					// 0x2D
			char unk2[180];					// 0xE1
			char unk3[180];					// 0x195

		};

		struct	// Ensure proper size.
		{
			char buffer[0xC03];				// 0x2D
		};
	};
};
#pragma pack(pop)

static_assert(sizeof(SceNotificationRequest) == 0xC30, "Size of SceNotificationRequest is not 0xC30");

int(*sceKernelSendNotificationRequest)(int api, char* buffer, size_t size, bool unk);

// Calling from userland:
void Notify(const char* icon, const char* fmt, ...)
{
	SceNotificationRequest buffer;

	va_list args;
	va_start(args, fmt);
	vsprintf(buffer.message, fmt, args);
	va_end(args);

	buffer.type = SceNotificationRequestType::NotificationRequest;
	buffer.Attribute = 0;
	buffer.useIconImageUri = 1;
	buffer.targetId = -1;
	strcpy(buffer.iconUri, icon);

	sceKernelSendNotificationRequest(NotificationAPI::Native, &buffer, sizeof(SceNotificationRequest), false);

	// What is sceKernelSendNotificationRequest doing?
	// 
	//		1. Opens the device "/dev/notification[0-4]" depending on the NotificationAPI passed in.
	//		2. Writes the data from the buffer to that device where the kernel forwards it to the listening side which for notification0/notification1 is SceShellUI.
	// 
	// NOTES: From what I can tell the json version is used to write to the notification data base.
}

int(*notification_write_from_kernel)(int api, char* buffer, size_t size, int ioflag);

// Calling from the kernel:
void kNotify(const char* icon, const char* fmt, ...)
{
	SceNotificationRequest buffer;

	va_list args;
	va_start(args, fmt);
	vsprintf(buffer.message, fmt, args);
	va_end(args);

	buffer.type = SceNotificationRequestType::NotificationRequest;
	buffer.Attribute = 0;
	buffer.useIconImageUri = 1;
	buffer.targetId = -1;
	strcpy(buffer.iconUri, icon);

	notification_write_from_kernel(NotificationAPI::Native, &buffer, sizeof(SceNotificationRequest), FNONBLOCK);

	// What is notification_write_from_kernel doing?
	// 
	//		- Has the same operation as above but writes to the buffer directly in the kernel.
	//
	// NOTES: You can find this easily because Sony will use this to pop notifications like "VideoOut:\nOnly %ld\nflips/second" on 9.00.
}
