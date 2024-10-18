# Base Addresses

| Offset          | Type            | Variable             | Description          |
| --------------- | --------------- | -------------------- | -------------------- |
| engine.dll + 0x616A7 | 4 Byte Integer (Unsigned?) | sv_cheats | If not 0, you can change more parameters about the server running. THIS VALUE SHOWN IN THE TERMINAL IS SAVED ELSEWHERE |
| engine.dll + 0x47C33C        | Float           | m_angRotation        | . |
| engine.dll + 0x5EC82C        | Integer         | m_iNumPlayers        | . |
| -- | | | |
| client.dll + 0x4C88E8        | Pointer         | m_dwLocalPlayer      | . |
| client.dll + 0x4F5D24        | DWORD           | m_dwForceJump        | . |
| client.dll + 0x4F5D30        | DWORD           | m_dwForceAttack      | . |

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