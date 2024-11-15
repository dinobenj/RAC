# Base Addresses

| Offset          | Type            | Variable             | Description          |
| --------------- | --------------- | -------------------- | -------------------- |
| engine.dll + 0x616A7         | 4 Byte Integer (Unsigned?) | sv_cheats | If not 0, you can change more parameters about the server running. THIS VALUE SHOWN IN THE TERMINAL IS SAVED ELSEWHERE |
| engine.dll + 0x47C33C        | 32 bit Float | m_angRotation        | Handles Player's Camera in the "up/down" direction |
| engine.dll + 0x47C340        | 32 bit Float | m_angRotation        | Handles Player's Camera in the "left/right" direction |
| engine.dll + 0x47C344        | 32 bit Float | m_angRotation        | Handles Player's Camera in the "Illegal" direction |
| engine.dll + 0x5EC82C        | Integer         | m_iNumPlayers        | Number of players on the server. If larger than actual amount, a crash occurs. If lower and excluding bots, it can work but is unstable. If lower on a player, they are disconnected. |
| -- | | | |
| client.dll + 0x4C88E8        | 32 bit Pointer         | m_dwLocalPlayer      | Player Pointer to the user's current player |
| client.dll + 0x4F5D24        | 1 Byte (Array Of Booleans)  | m_dwForceJump  | `2^0` bit will cause the player to simulate pressing the spacebar. So keeping the value at 1 won't work. `2^1` but is cleared often, but not sure on purpose, and `2^2` bit is usually always active, not sure on purpose either. All other bits are irrelevant. |
| client.dll + 0x4F5D30        | 1 Byte (Array Of Booleans)  | m_dwForceAttack      | Same rules as `client.dll + 0x4F5D24` |
| client.dll + 0x4F5D6C        | 1 Byte (Array Of Booleans)  | m_dwForceReload     | Same rules as `client.dll + 0x4F5D24` |
| client.dll + 0x4F5D60        | 1 Byte (Array Of Booleans)  | m_dwForceCrouch     | Same rules as `client.dll + 0x4F5D24` |
| client.dll + 0x4D5AE4        | 1 6 byte struct. 32 bit pointer, and 12 other bytes | Array_Of_Players | Contains all players in the match in an array separated by 0x10 bytes each starting at this address. Fixed Size. Will only be allocated once at start of game to max player limit. |
| -- | | | |
| server.dll + 0x54EACC        | 32 bit float | Pistol_Starting_Reserve | Starting Reserve ammo for 9x19MM Sidearm (maybe for all pistols??) |
| server.dll + 0x4F615C        | 16 byte struct. 32 bit pointer, and 12 other bytes | Array_Of_players | Server-side array that contains all players in the match. look above for more info |
| server.dll + 0x4F750C        | 16 byte struct. 32 bit pointer, and 12 other bytes | Array_Of_Weapons | Around here is the start of the array for every weapon in the game. To get pointer for weapon you picked up, use a breakpoint on `Server.dll + 275CE0` and pick it up|

# Player Pointer (from client.dll)

| Offset          | Type            | Variable             | Description          |
| --------------- | --------------- | -------------------- | -------------------- |
| + 0x0094          | 4 byte Integer  | m_iHealth            | health as displayed on screen (can't be changed though) |
| + 0x009C          | 4 byte Integer  | m_iTeamNum           | 0 if deciding, 1 Spectate, 2 Terrorist, 3 Counter Terrorist |
| + 0x0350          | Boolean (1 byte)| m_fFlags             | 0 if in air, 1 if grounded, (2 if trying to un-crouch but environment prevents it?), 3 if un-crouching (not fully), 5 if crouching (not fully), 6 if crouched in air, 7 if fully crouched |
| + 0x0E48          | 4 Byte Float    | m_vecPunchAngle      | ???? Always 0 ?????? |
| + 0x144C          | 4 Byte Float    | Total Flash Time     | A float that increases per time flashed. If a strong flash it increases a lot (up to 10), if weak it increases less (like 2) |
| + 0x1450          | 4 Byte Float    | m_flFlashMaxDuration | Either 255 or 200. Not sure what it means |
| + 0x1454          | 4 Byte Float    | Last Flash's Strength | A float between 0-7 representing the strength of the flash |
| + 0x14F0	        | 4 byte Integer  | m_iCrosshairId	     | ?? unchangeable ?? |
| + 0x0d80          | 3 bytes (booleans?)| Weapon Held       | The three bytes here only change when swapping weapons. First byte seems to be Entity ID. Not sure on other two bytes |
| + 0xf4            | 4 Byte Float       | X-pos Velocity    | Velocity in X-pos. Not sure what units are. |
| + 0xf8            | 4 Byte Float       | Y-pos Velocity    | Velocity in Y-pos. Not sure what units are. |
| + 0xfC            | 4 Byte Float       | Z-pos Velocity    | Velocity in Z-pos. Not sure what units are. |
| + 0x290           | 4 Byte Float       | X-position       | Doesn't seem to be the same as the value in "cl_showpos", but only changes when x-position changes. |
| + 0x294           | 4 Byte Float       | Y-position       | Doesn't seem to be the same as the value in "cl_showpos", but only changes when y-position changes. |
| + 0x298           | 4 Byte Float       | Z-position       | Doesn't seem to be the same as the value in "cl_showpos", but only changes when z-position changes. |
| + 0xCC0           | Array of 4 byte ?Values? (48 in length) | Player Inventory | An Array initially set to -1 in every index. The next picked up weapon takes the first slot that = -1 and puts a pointer to the weapon there. |
| + 0xC56           | Array of 2 byte Integers (52 in length)   | Reserve Ammo | An Array initially set to 0 in ever index. The weapon picked up in this slot index (look at 'Player Inventory') reserve ammo is stored here. Not sure why lengths don't match up...... |

# Weapon Pointer (from server.dll)

| Offset          | Type            | Variable             | Description          |
| --------------- | --------------- | -------------------- | -------------------- |
| + 0x570         | 4 byte Integer  | Reserve Ammo         | The reserve ammo within the weapon. 0 if held, set to a value once dropped |

# Function in the code

Client.dll + 0x189150 is a function run when switching weapons, picking them up, and dropping them


Server.dll + 0xC91C0 is a function run when reloading a gun (specifically when your reserve and magazine ammo swap)
           + 0xC91DC - EDI value is weapon slot it takes up in player inventory? It changes what weapon actually loses its reserve ammo
                     - ESI is amount of ammo to remove
           + `mov eax,[ebx+edi*4+000006A4]` is the same as `[Pointer value of player in server.dll + 0x4F615C] + (Weapon inventory slot within player * 4) + 0x6A4`

Server.dll + CA0B0 is a function that deals with setting the reserve ammo for a weapon when dropping/picking one up

Server.dll + 275CE0 is a getter for the ammo within a weapon (at least when its on the ground and just picked up)