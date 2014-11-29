#ifndef HOTEL_H
#define HOTEL_H

extern STRLEN;

class hotel
{
    public:
        /** Default constructor */
        hotel();
        ~hotel();


        // Getters

        /** Access name
         **
         ** @return The current value of name
         */
        char* getName() { return name; }

        /** Access address
         **
         ** @return The current value of address
         */
        char* getAddress() { return address; }

        /** Access zipcode
         **
         ** @return The current value of zipcode
         */
        char* getZipcode() { return zipcode; }

        /** Access email
         **
         ** @return The current value of email
         */
        char* getEmail() { return email; }

        /** Access filename
         **
         ** @return The current value of filename
         */
        char* getFilename() { return filename; }

        /** Access phone
         **
         ** @return The current value of phone
         */
        int getPhone() { return phone; }

        /** Access fax
         **
         ** @return The current value of fax
         */
        int getFax() { return fax; }

        /** Access breakfast_price
         **
         ** @return The current value of breakfast_price
         */
        int getBreakfastPrice() { return breakfast_price; }

        /** Access additional_bed_cost
         **
         ** @return The current value of additional_bed_cost
         */
        int getAdditionalBedCost() { return additional_bed_cost; }

        /** Access amount_facilities
         **
         ** @return The current value of amount_facilities
         */
        int getAmountFacilities() { return amount_facilities; }


        // Setters


        /** Set name
         **
         ** @param val New value to set
         */
        void setName(char* val) { name = val; }

        /** Set address
         **
         ** @param val New value to set
         */
        void setAddress(char* val) { address = val; }

        /** Set zipcode
         **
         ** @param val New value to set
         */
        void setZipcode(char* val) { zipcode = val; }

        /** Set email
         **
         ** @param val New value to set
         */
        void setEmail(char* val) { email = val; }

        /** Set filename
         **
         ** @param val New value to set
         */
        void setFilename(char* val) { filename = val; }

        /** Set phone
         **
         ** @param val New value to set
         */
        void setPhone(int val) { phone = val; }

        /** Set fax
         **
         ** @param val New value to set
         */
        void setFax(int val) { fax = val; }

        /** Set breakfast_price
         **
         ** @param val New value to set
         */
        void setBreakfastPrice(int val) { breakfast_price = val; }

        /** Set additional_bed_cost
         **
         ** @param val New value to set
         */
        void setAdditionalBedCost(int val) { additional_bed_cost = val; }

        /** Set amount_facilities
         **
         ** @param val New value to set
         */
        void setAmountFacilities(int val) { amount_facilities = val; }

    protected:
    private:
        char name[NAMELENGTH];
        char address[STRLEN];
        char zipcode[STRLEN];
        char email[STRLEN];
        char filename[STRLEN];
        int phone;
        int fax;
        int breakfast_price;
        int additional_bed_cost;
        int amount_facilities;
};

#endif // HOTEL_H
