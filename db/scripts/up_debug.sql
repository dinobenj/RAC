CREATE TABLE DebuggedProcesses (
    id SERIAL PRIMARY KEY,        
    ProcessName VARCHAR(255) NOT NULL,
    ProcessPid INTEGER NOT NULL,    
    DebugStartTime TIMESTAMP         
);
