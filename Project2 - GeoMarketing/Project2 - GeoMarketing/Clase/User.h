#pragma once

class User {

	private:
		int id,nrCumparaturi;
		double homeX, homeY;
		int discount;
	public:
		User() {
			id = 0;
			homeX = 0;
			homeY = 0;
			discount = 0;
			nrCumparaturi=0;
		}
		
		~User() {}
		
		User(int id, double homeX, double homeY) {
			this->id = id;
			this->homeX = homeX;
			this->homeY = homeY;
		}
		
		User(const User &other) {
			this->id = other.id;
			this->homeX = other.homeX;
			this->homeY = other.homeY;
			this->discount = other.discount;
			this->nrCumparaturi = other.nrCumparaturi;
		}

		int getId() {
			return id;
		}
		double getX() {
			return homeX;
		}
		double getY() {
			return homeY;
		} 
		int getDiscount() {
			return  discount;
		}
		float getRaport() {
			return (float)discount/nrCumparaturi;
		}

		void setId(int id) {
			this->id = id;
		}
		void setX(double homeX) {
			this->homeX = homeX;
		}
		void setY(double homeY){
			this->homeY = homeY;
		}
		
		void setDiscount(int discount) {
			if( discount != -1 ) {
				nrCumparaturi++; 
				this->discount += discount;
			}
		}

		bool operator>(User& u)
		{
			if (this->getRaport() < u.getRaport())
				return true;
			return false;
		}

};
