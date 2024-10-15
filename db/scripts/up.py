import dotenv
import asyncpg
import asyncio
import os
import glob


async def up_tables():
    #onlyfiles = [f for f in os.listdir("./") if os.path.isfile(os.path.join("./", f))]
    sql_files = glob.glob("*.sql")
    sql_files.sort()
    print(sql_files)
    dotenv.load_dotenv()
    conn = await asyncpg.connect(os.getenv("POSTGRES_CONN_STR"))
    for file in sql_files:
        if "down" not in file:
            print(f"Running {file}")
            fd = open(file)
            sql_script_text = fd.read()
            fd.close()
            await conn.execute(sql_script_text)

    


if __name__ == "__main__":
    asyncio.run(up_tables())
