
class Animal {
public:
	Animal(string me);
	virtual ~Animal() {};
	virtual void speak() const = 0 ;
	string name() const {
		return m_name;
	};
	virtual string moveAction() const {
		return "walk";
	};
private:
	string m_name;
};

class Cat : public Animal {
public:
	Cat(string me) : Animal(me) {};
	virtual ~Cat() {
		cout << "Destroying " << name() << " the cat" << endl;
	}
	virtual void speak() const {
		cout << "Meow";
	}
};

class Pig : public Animal {
public:
	Pig(string me, double weight) : Animal(me), m_weight(weight) {
	};
	virtual ~Pig() {
		cout << "Destroying " << name() << " the pig" << endl;
	}
	virtual void speak() const {
		if (m_weight < 170)
			cout << "Oink";
		else
			cout << "Grunt";
	}
private:
	double m_weight;
};

class Duck : public Animal {
public:
	Duck(string me) : Animal(me) {};
	virtual ~Duck() {
		cout << "Destroying " << name() << " the duck" << endl;
	}
	virtual void speak() const {
		cout << "Quack";
	}
	virtual string moveAction() const {
		return "swim";
	}
};

Animal::Animal(string me) {
	m_name = me;
}





