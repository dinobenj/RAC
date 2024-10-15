import asyncpg
import os
import asyncio
from dotenv import load_dotenv

async def down_tables() :
    load_dotenv()
    conn = await asyncpg.connect(os.getenv("POSTGRES_CONN_STR"))
    await conn.execute("DROP TABLE IF EXISTS users CASCADE")
    await conn.execute("DROP TABLE IF EXISTS sessions CASCADE")
    await conn.execute("DROP TABLE IF EXISTS dll CASCADE")
    await conn.execute("DROP TABLE IF EXISTS keylogger CASCADE")
    await conn.execute("DROP TABLE IF EXISTS memcheck CASCADE")
    print("Tables dropped")

if __name__ == "__main__":
    asyncio.run(down_tables())