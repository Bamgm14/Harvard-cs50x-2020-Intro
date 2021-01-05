import socket as s
import threading as t
import base64 as b64
import json
import sqlite3 as sql
import Digimon as d
import pickle as p
conn = sql.connect(".\\Users.sqlite3")
curse = conn.cursor()
curse.execute("create table if not exists users(id INTEGER PRIMARY KEY AUTOINCREMENT, digimon blob)")
con = s.socket()
users = {}
con.bind(('127.0.0.1',6666))
con.listen(5)
def ToJavaBytes(strs):
    return (len(strs)+1).to_bytes(2, byteorder='big')+strs.encode("UTF-8")+b"\n"
#def Register()
while True:
    digi = d.Digimon()
    try:
        c,addr = con.accept()
        byte = c.recv(1024)
        #print(byte)
        user = byte[2:].decode()
        #print(user)
        c.send(ToJavaBytes("Connected"))
        byte = c.recv(1024)
        strs = byte[2:].decode()
        #print(strs)
        if strs == "Register":
            digi = d.Digimon()
            if user == "None":
                #print("A")
                curse.execute("insert into users (digimon) values (?)",(p.dumps(digi),))
                curse.execute("select count(id) from users")
                user = str(curse.fetchall()[0][0])
                c.send(ToJavaBytes(str(user)))
            else:
                #print("B")
                curse.execute("update users set digimon = ? where id = ?",(p.dumps(digi),int(user)))
                c.send(ToJavaBytes(str(user)))           
        elif strs == "Play":
            #print("E")
            curse.execute("select digimon from users where id = ?",(int(user),))
            digi = p.loads(curse.fetchall()[0][0])
            print(digi,type(digi))
            c.send(ToJavaBytes(digi.play()))
            curse.execute("update users set digimon = ? where id = ?",(p.dumps(digi),int(user)))
        elif strs == "PVE":
            #print("F")
            curse.execute("select digimon from users where id = ?",(int(user),))
            digi = p.loads(curse.fetchall()[0][0])
            c.send(ToJavaBytes(digi.pve()))
            curse.execute("update users set digimon = ? where id = ?",(p.dumps(digi),int(user)))
        elif strs == "Digivolve":
            #print("D")
            curse.execute("select digimon from users where id = ?",(int(user),))
            digi = p.loads(curse.fetchall()[0][0])
            c.send(ToJavaBytes(digi.__digivolve__()))
            curse.execute("update users set digimon = ? where id = ?",(p.dumps(digi),int(user)))
        else:
            #print("C")
            if user != "None":
                curse.execute("select digimon from users where id = ?",(int(user),))
                digi = curse.fetchall()[0][0]
                digi = p.loads(digi)
                #print(digi)
            else:
                c.close()
                continue
        digi = digi.digimoninfo()
        test = json.dumps(digi)
        #print(len(test))
        c.send(ToJavaBytes(test))
        conn.commit()
        c.close()
    except Exception as e:
        print(e)
    #c.send((chr((len(test)//256)*(len(test)%256))+chr(len(test)%256)+test).encode())
#/scoreboard players add @p Points 1