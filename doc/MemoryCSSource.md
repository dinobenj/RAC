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

# Player pointer

| Offset          | Type            | Variable             | Description          |
| --------------- | --------------- | -------------------- | -------------------- |
| + 0x0094          | Integer         | m_iHealth            | . |
| + 0x009C          | Integer         | m_iTeamNum           | . |
| + 0x0290          | Float           | m_vecOrigin          | . |
| + 0x0350          | Float           | m_fFlags             | . |
| + 0x0D80          | Integer         | m_hActiveWeapon      | . |
| + 0x0E48          | Float           | m_vecPunchAngle      | . |
| + 0x144C          | Float           | m_flFlashMaxAlpha    | . |
| + 0x1450          | Float           | m_flFlashMaxDuration | . |
| + 0x14F0	        | Integer	      | m_iCrosshairId	     | . |