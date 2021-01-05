#imports
import random as r
import sqlite3 as sql
import pickle as p
import math as m
import time as t

#errors
class DigiError(Exception):
    pass

#functions
def dict_factory(cursor, row):
    dct = {}
    for idx, col in enumerate(cursor.description):
        try:
            dct[col[0]] = p.loads(row[idx])
        except:
            dct[col[0]] = row[idx]
    return dct

#digimon
class Digimon:
    def __init__(self,digimon=None,digidb='Digidb.sqlite3'):
        self.schema=['id','lvl','experience',
        'name','stage','type','attribute',
        'dedigivolve','corruption','time',
        'happiness','evolutionline','bond','stats','extra','url']
        builder={'corruption': r.random(),
        'happiness': r.random(),'evolutionline': [],
        'bond': r.random()/2,'lvl': 1,'experience': 0,
        'time': t.time()}
        self.digidb=digidb
        with sql.connect(self.digidb) as con:
            con.row_factory = dict_factory
            c=con.cursor()
            c.execute('select * from Digimon')
            self.data=c.fetchall()
            if not digimon:
                data=[x for x in self.data if x['stage']=="Baby"]
                self.digimon=r.choice(data)
                for x in builder:
                    self.digimon[x]=builder[x]
                return None
            else:
                if type({})!=type(digimon):
                    try:
                        data=[x for x in self.data if x['id']==int(digimon)]
                    except:
                        data=[x for x in self.data if x['name']==digimon]
                    if len(data)!=1:
                        raise DigiError("More than one digimon or no digimon retrieved")
                    self.digimon=data[0]
                    for x in builder:
                        self.digimon[x]=builder[x]
                    return None                        
                else:
                    if sorted(self.schema)!=sorted(list(digimon.keys())):
                        missing=[]
                        for x in list(digimon.keys()):
                            if x not in self.schema:
                                missing.append(x)
                        raise DigiError("Invalid Digimon Format:{}".format(str(missing)))
                    self.digimon=digimon
                    return None
    def __str__(self):
        return str(self.digimon)
    def __repr__(self):
        return self.digimon
    def play(self):
        points=self.__sigmoidhalf__(r.random())
        builder={'experience': 2*r.random(),
        'happiness': points,
        'bond': points/4,
        'corruption': (-1/16)*r.random()}
        for x in builder:
            self.digimon[x]+=builder[x]
        self.__updator__()
        if builder['happiness']>0:
            return "You had fun playing!"
        else:
            return "You didn't fun playing..."
    def pve(self):
        builder={'experience': 2*r.random(),
        'bond': self.__sigmoidhalf__(r.random())}
        for x in builder:
            self.digimon[x]+=builder[x]
        self.__updator__()
        if builder['bond']>0:
            return "You won the battle."
        else:
            return "You lost the battle."
    def digimoninfo(self):
        return self.digimon
    def pvp(self,digimon):
        pass
#backgrounds
    def __digivolve__(self,extra=None):
        name=self.digimon['name']
        data=[x for x in self.data if self.digimon['id'] in x['dedigivolve']]
        if len(data)==0:
            return f"Your {name} have reached the final evolution."
        if self.digimon['bond']<1:
            return f"Your {name} doesn't have a strong enough bond with you."
        if not extra:
            data=[x for x in data if not x['extra']]
            if len(data)==0:
                return f"Your {name} needs a extra condition to reach a higher level."
            dct={'Free':[],'Vaccine':[],'Data':[],'Virus':[]}
            for x in data:
                dct[x['type']]+=[x]
            possible=dct['Free']
            if self.digimon['corruption']<=0.33 and self.digimon['happiness']>=0.67:
                possible+=dct['Vaccine']
            if (self.digimon['corruption']<=0.67 and self.digimon['happiness']>=0.67):
                possible+=dct['Data']
            if self.digimon['corruption']>=0.67 and self.digimon['happiness']<=0.33:
                possible+=dct['Virus']
            if len(possible)==0:
                return f"Your {name} do not have the stats to digivolve."
        if extra:
            possible=[]
            data=[x for x in data if x['extra']]
            try:
                extra.item
                for x in data:
                    try:
                        if x['extra'][extra.item['type']]==extra.item['name']:
                            possible.append(x)
                    except:
                        pass
                if len(possible)==0:
                    return f"{extra.item['name']} cannot be used with {name}"
            except:
                extra.digimon
                for x in data:
                    if extra.digimon['id'] in x['extra']['DNA']:
                        possible.append(x)
                if len(possible)==0:
                    return f"{extra.digimon['name']} cannot be jogress with {name}"
                name+=f" and {extra.digimon['name']}"
        digimon=r.choice(possible)
        self.digimon['evolutionline'].append(self.digimon['id'])
        for x in digimon:
            self.digimon[x]=digimon[x]
        for y in range(0,self.digimon['lvl']):
            for x in self.digimon['stats']:
                lvl=r.randint(0,1000*(y+1))/(50*(y+1))
                if x in ['hp']:
                    lvl*=10
                self.digimon['stats'][x]+=round(lvl)
        self.digimon['bond']-=1
        self.__updator__()
        return f"Congrats, your {name} evolved into a {self.digimon['name']}"
    def __updator__(self):
        if m.exp(self.digimon['lvl'])<=self.digimon['experience']:
            self.digimon['lvl']+=1
            for x in self.digimon['stats']:
                lvl=r.randint(0,1000*self.digimon['lvl'])/(50*self.digimon['lvl'])
                if x in ['hp']:
                    lvl*=10
                self.digimon['stats'][x]+=round(lvl)
        self.digimon['corruption']+=r.random()*(t.time()-self.digimon['time'])/(60**2)
        self.digimon['time']=t.time()
    def __sigmoidhalf__(self,x):
        return 4*(1/(1+m.exp(-10*(x-0.5)))-0.5)
class Item:
    def __init__(self,item=None,digidb='Digidb.sqlite3'):
        self.schema=['id','name','type']
        self.digidb=digidb
        with sql.connect(self.digidb) as con:
            con.row_factory = dict_factory
            c=con.cursor()
            c.execute("select * from Item")
            self.data=c.fetchall()
            if not item:
                self.item=r.choice(self.data)
                return None
            if type({})!=type(item):
                try:
                    item=[x for x in self.data if x['id']==int(item)]
                except:
                    item=[x for x in self.data if x['name']==item]
                if len(item)!=1:
                    raise DigiError("More than one item or no item retrieved")
                self.item=item[0]
                return None
            else:
                if sorted(self.schema)!=sorted(list(item.keys())):
                    missing=[]
                    for x in list(item.keys()):
                        if x not in self.schema:
                            missing.append(x)
                    raise DigiError("Invalid Digimon Format:{}".format(str(missing)))
                self.item=item
                return None

if __name__=='__main__':
    import time as t
    Digi=Digimon()
    """
    for x in range(3000):
        print(Digi.digimoninfo())
        print(Digi.pve())
        print(Digi.play())
        print(Digi.__digivolve__())
        t.sleep(30)
    """
    print(Digi.digimoninfo())