class Person{
private int id
private String name
protected int age
protected list<Person> foes
protected list<Person> friends
void addFoe(Person foe)
{
 foes.add(foe);
 foe.addFoe(this);
}
public void addFriend(Person friend)
{
 friends.add(friend);
 friend.addFriend(this);
}
bool isFriend(Person pers){
return friends.contain(pers)
}
bool isFoe(Person pers){
return foes.contain(pers)
}
public Person(Person pers){
	this = pers.clone();
	

}
}




class Worker extends Person{
int productivity
int getProductivity(){
	return productivity;}
void setProductivity(int newProductivity)
{
	productivity =  newProductivity
}

}


class Master extends Person{
float  productivity

float getProductivity(){
	return productivity;}
void setProductivity(int newProductivity)
{
	productivity =  newProductivity
}
public Master(Worker worker, float newProductivity)
{
	this.productivity = newProductivity;
	super(worker);
}
}




class Workplace{
list<Worker> workers;
list<Master> masters;
float work;
float production;
int foes_amount = 0;
int friends_amount = 0;
private void addPerson(Person newbie){
	for(int i = 0; i < workers.size(); i++){
		if(newbie.isFoe(workers[i]))
			foes_amount++;
		else if(newbie.isFriend(workers[i]))
			friends_amount++;
		}
		for(int i = 0; i < masters.size(); i++){
		if(newbie.isFoe(masters[i]))
			foes_amount++;
		else if(newbie.isFriend(masters[i]))
			friends_amount++;
		}
		updateProduction();
	}
void updateProduction(){
	for(int i = 0; i < workers.size(); i++){
		production+=workers[i].getProductivity();
		}
	for(int i = 0; i < masters.size(); i++){
		production=production*masters[i].getProductivity();
	}
		production-=foes_amount/2;
		production-=friends_amount/3;
	}
int estimateDaysLeft(){ 
	return округлитьвверх(work/production);
}
private void deletePerson(Person newbie){
	for(int i = 0; i < workers.size(); i++){
			if(newbie.isFoe(workers[i]))
				foes_amount--;
			else if(newbie.isFriend(workers[i]))
				friends_amount--;
			}
			for(int i = 0; i < masters.size(); i++){
			if(newbie.isFoe(masters[i]))
				foes_amount--;
			else if(newbie.isFriend(masters[i]))
				friends_amount--;
			}
		
		
		updateProduction();
	}
void addWorker(Worker newbie){
	workers.add(newbie);
	addPerson(newbie);
}void addMaster(Master newbie){
	masters.add(newbie);
	addPerson(newbie);
}void deleteWorker(Worker newbie){
	if(workers.contain(newbie){
		workers.remove(newbie);
		deletePerson(newbie);
	}
}void deleteMaster(Master newbie){
	if(masters.contain(newbie){
		masters.remove(newbie);
		deletePerson(newbie);
	}
}void deleteById(int id){
	for(int i = 0; i < workers.size(); i++)
		if(workers[i].getId() == id)
			deleteWorker(workers[i]);
	for(int i = 0; i < masters.size(); i++)
		if(masters[i].getId() == id)
			deleteMaster(masters[i]);	
}

bool isWorking(Person pers){
	return workers.contain(pers)||masters.contain(pers);
}
bool  isWorking(int id){
	for(int i = 0; i < workers.size(); i++)
		if(workers[i].getId() == id)
			return true;
	for(int i = 0; i < masters.size(); i++)
		if(masters[i].getId() == id)
			return true;	
	return false;
}

void work(){
	work = max(0, work - production);
	\\формирование случайной пары друзей и  врагов хз как сделать...(
	updateProduction();
}
float getProduction(){
	return production;
}
}




int main(){
list<Person> brigade;
list<Workplace> workplaces;
while(true){
//постоянно читаем и определяем команду которая пришла
new_workplace(work_amount):
	workplaces.add(new Workplace(work_amount))
edit_workplace(id, work_amount):
	workplaces[id].setWork(work_amount);
add_worker(workplace_id, worker_id):
	for(int i = 0; i<workplaces.size();  i++){
		if(workplaces[i].isWorking(worker_id)){
			deleteById(worker_id)
		}
	}
	for(int i = 0; i<brigade.size(); i++){
	if(brigade[i].getId() == worker_id)
		workplaces[workplace_id].addWorker(brigade[i]);
dismiss_worker(worker_id)	
	for(int i = 0; i<workplaces.size();  i++){
		if(workplaces[i].isWorking(worker_id)){
			deleteById(worker_id)
		}
	}
	for(int i = 0; i<brigade.size(); i++){
		if(brigade[i].getId() == worker_id)
			brigade.remove(brigade[i]);
get_production (workplace_id)	
		print(workplaces[workplace_id].getProduction());
summary	
	for(int i = 0; i<workplaces.size(); i++){
		println(i + ':' + (workplaces[i].estimateDaysLeft()<=1));
	//выведет тру для тех которые закончат сегодня
	}
worst	
	ans = 0 
	for(int i = 0; i<workplaces.size(); i++){
		if(workplaces[i].estimateDaysLeft() > workplaces[ans].estimateDaysLeft())
			ans = i;
	}
	print(ans+':'+workplaces[ans].estimateDaysLeft());
work	
	for(int i = 0; i<workplaces.size();  i++){
		workplaces[i].work();
	}
edit_worker(id, new_productivity)
	for(int i = 0; i<brigade.size(); i++){
		if(brigade[i].getId() == id){
			brigade[i].setProductivity(newProductivity);
			for(int j = 0; j<workplaces.size();  j++){
				if(workplaces[j].isWorking(id)){
					workplaces[j].deleteById(id)
					workplaces[j].addWorker(brigade[i]);
				}
			}
		}
	}
add_foe(id, foe_id)
	for(int i = 0; i<brigade.size(); i++){
		if(brigade[i].getId() == id){
			for(int j = 0; j<brigade.size(); j++){
				if(brigade[j].getId() == foe_id){
					brigade[i].addFoe(brigade[j]);
					for(int k = 0; k<workplaces.size();  k++){
						if(workplaces[k].isWorking(id)){
							workplaces[k].deleteById(id)
							workplaces[k].addWorker(brigade[i]);
						}
					}
					for(int k = 0; k<workplaces.size();  k++){
						if(workplaces[k].isWorking(foe_id)){
							workplaces[k].deleteById(foe_id)
							workplaces[k].addWorker(brigade[j]);
						}
					}
				}
			}	
		}
	}
}
add_friend(id, friend_id)
	for(int i = 0; i<brigade.size(); i++){
		if(brigade[i].getId() == id){
			for(int j = 0; j<brigade.size(); j++){
				if(brigade[j].getId() == friend_id){
					brigade[i].addFoe(brigade[j]);
					for(int k = 0; k<workplaces.size();  k++){
						if(workplaces[k].isWorking(id)){
							workplaces[k].deleteById(id)
							workplaces[k].addWorker(brigade[i]);
						}
					}
					for(int k = 0; k<workplaces.size();  k++){
						if(workplaces[k].isWorking(friend_id)){
							workplaces[k].deleteById(friend_id)
							workplaces[k].addWorker(brigade[j]);
						}
					}
				}
			}	
		}
	}
}
promote(id, new_productivity)
	for(int i = 0; i<brigade.size(); i++){
		if(brigade[i].getId() == id){
			for(int j = 0; j<workplaces.size();  j++){
				if(workplaces[j].isWorking(id)){
					workplaces[j].deleteById(id)
					workplaces[j].addWorker(new Master(brigade[i], new_productivity));
					brigade.add(new Master(brigade[i], new_productivity));
					brigade.remove(brigade[i])
					
					
				}
			}
		}
	}








