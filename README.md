# PS4-Notify
A different way of calling the notify function on the ps4 for homebrew development.

![alt text](https://i.imgur.com/W2Zpz33.png)

## Examples

``` C++
Notify("cxml://psnotification/tex_default_icon_notification", "Hello World");
```

You dont have to use one of the default ps4 icons though using a web url will work as well.

``` C++
Notify("http://www.somewhere.com/SomeImage.png", "Hello World"); 
```

You can also use an image from the HDD but it must be a location visible to ShellUI.

``` C++
Notify("file://user/data/SomeImage.png", "Hello World");
Notify("/user/data/SomeImage.png", "Hello World");
```

## Calling from Userland
``` C++
void Notify(const char* icon, const char* fmt, ...)
{
	SceNotificationRequest buffer;

	va_list args;
	va_start(args, fmt);
	vsprintf(buffer.message, fmt, args);
	va_end(args);

	buffer.type = SceNotificationRequestType::Message;
	buffer.Attribute = 0;
	buffer.useIconImageUri = 1;
	buffer.targetId = -1;
	strcpy(buffer.iconUri, icon);

	sceKernelSendNotificationRequest(NotificationAPI::Native, &buffer, sizeof(SceNotificationRequest), false);
}
```

### What is sceKernelSendNotificationRequest doing?
1. Opens the device "/dev/notification[0-5]" depending on the NotificationAPI passed in.
2. Writes the data from the buffer to that device where the kernel forwards it to the listening side which for notification0/notification1 is SceShellUI.

**NOTES:** From what I can tell the json version is used to write to the notification data base.
You can call the notify function like this using one of the default ps4 icons.

## Calling from Kernel
``` C++
void Notify(const char* icon, const char* fmt, ...)
{
	SceNotificationRequest buffer;

	va_list args;
	va_start(args, fmt);
	vsprintf(buffer.message, fmt, args);
	va_end(args);

	buffer.type = SceNotificationRequestType::Message;
	buffer.Attribute = 0;
	buffer.useIconImageUri = 1;
	buffer.targetId = -1;
	strcpy(buffer.iconUri, icon);

	notification_write_from_kernel(NotificationAPI::Native, &buffer, sizeof(SceNotificationRequest), FNONBLOCK);
}
```

### What is notification_write_from_kernel doing?
- Has the same operation as sceKernelSendNotificationRequest but writes to the buffer directly in the kernel.

**NOTES:** You can find this easily because Sony will use this to pop notifications like "VideoOut:\nOnly %ld\nflips/second" on 9.00.

## Notify Definitions
``` C++
enum SceNotificationRequestType
{
	Message = 0,
	MessageMsgId = 1,
	MessageUserId = 2,
	MessageDeviceId = 3,
	MessageDeviceIdRelatedToUser = 4,
	MessageText = 5,
	MessageTextRelatedToUser = 6,
	MessageErrorCode = 7,
	MessageAppId = 8,
	MessageAppInfo = 9,
	MessageTitleRelatedToUser = 10,
	MessageParams = 11,
	MessageUserName = 12,
	MessageUserNameInfo = 13,
	MessageAddressing = 14,
	MessageAddressingDeviceId = 15,
	MessageAddressingUserName = 16,
	MessageAddressingUserId, = 17,

	DebugMessage = 100,
	TrcCheckMessage = 101,
	NpDebugMessage = 102,
	WebDebugMessage = 102,
	UNK_103 = 103,
};

enum SystemNotificationPriority
{
	Default = 0,
	High = 1,
	Special = -1
};

enum SystemNotificationAttribute
{
	ShowVideoPlayback = 1,
	ShowVR = 2,
	ShowKratos = 4,
	All = 7,
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
	uint32_t DeviceId;						// 0x18
	uint32_t AddressingUserId;				// 0x1C
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
			char arg1[180];					// 0x2D
			char arg2[180];					// 0xE1
			char arg3[180];					// 0x195

		};

		struct	// Ensure proper size.
		{
			char buffer[0xC03];				// 0x2D
		};
	};
};
#pragma pack(pop)
static_assert(sizeof(SceNotificationRequest) == 0xC30, "Size of SceNotificationRequest is not 0xC30");

int(*sceKernelSendNotificationRequest)(int api, char* buffer, size_t size, bool blocking);
int(*notification_write_from_kernel)(int api, char* buffer, size_t size, int ioflag);
```

## Some Icon URIs I have dumped
There is probably more than these but these I have tested and confirmed they do work.
```
cxml://psnotification/tex_icon_system                 // Playstation buttons
cxml://psnotification/tex_icon_ban                    // Circle with a slash
cxml://psnotification/tex_default_icon_notification   // i in a chat bubble
cxml://psnotification/tex_default_icon_message
cxml://psnotification/tex_default_icon_friend
cxml://psnotification/tex_default_icon_trophy
cxml://psnotification/tex_default_icon_download
cxml://psnotification/tex_default_icon_upload_16_9
cxml://psnotification/tex_default_icon_cloud_client   // ps now logo
cxml://psnotification/tex_default_icon_activity
cxml://psnotification/tex_default_icon_smaps          // bullhorn
cxml://psnotification/tex_default_icon_shareplay
cxml://psnotification/tex_default_icon_tips
cxml://psnotification/tex_default_icon_events
cxml://psnotification/tex_default_icon_share_screen
cxml://psnotification/tex_default_icon_community
cxml://psnotification/tex_default_icon_lfps
cxml://psnotification/tex_default_icon_tournament
cxml://psnotification/tex_default_icon_team
cxml://psnotification/tex_default_avatar
cxml://psnotification/tex_icon_capture
cxml://psnotification/tex_icon_start_rec
cxml://psnotification/tex_icon_stop_rec
cxml://psnotification/tex_icon_live_prohibited
cxml://psnotification/tex_icon_live_start
cxml://psnotification/tex_icon_loading
cxml://psnotification/tex_icon_loading_16_9
cxml://psnotification/tex_icon_countdown
cxml://psnotification/tex_icon_party
cxml://psnotification/tex_icon_shareplay
cxml://psnotification/tex_icon_broadcast
cxml://psnotification/tex_icon_psnow_toast
cxml://psnotification/tex_audio_device_headphone
cxml://psnotification/tex_audio_device_headset
cxml://psnotification/tex_audio_device_mic
cxml://psnotification/tex_audio_device_morpheus
cxml://psnotification/tex_device_battery_0
cxml://psnotification/tex_device_battery_1
cxml://psnotification/tex_device_battery_2
cxml://psnotification/tex_device_battery_3
cxml://psnotification/tex_device_battery_nocharge
cxml://psnotification/tex_device_comp_app
cxml://psnotification/tex_device_controller
cxml://psnotification/tex_device_jedi_usb
cxml://psnotification/tex_device_blaster
cxml://psnotification/tex_device_headphone
cxml://psnotification/tex_device_headset
cxml://psnotification/tex_device_keyboard
cxml://psnotification/tex_device_mic
cxml://psnotification/tex_device_morpheus
cxml://psnotification/tex_device_mouse
cxml://psnotification/tex_device_move               // ps move controller
cxml://psnotification/tex_device_remote
cxml://psnotification/tex_device_omit
cxml://psnotification/tex_icon_connect              // Weird blury thing
cxml://psnotification/tex_icon_event_toast          // Calendar
cxml://psnotification/tex_morpheus_trophy_bronze
cxml://psnotification/tex_morpheus_trophy_silver
cxml://psnotification/tex_morpheus_trophy_gold
cxml://psnotification/tex_morpheus_trophy_platinum
cxml://psnotification/tex_icon_champions_league     // The OG foot ball lol
```
