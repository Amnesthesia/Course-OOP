
#ifndef ROOM_H
#define ROOM_H


class room
{
    public:
        room();
        ~room();
        int Getroom_nr() { return room_nr; }

        // Getters
        int getAmountBeds() { return amount_beds; }
        bool getBreakfastIncluded() { return breakfast_included; }

        // Setters
        void setRoomNumber(int val) { room_nr = val; }
        void setAmountBeds(int val) { amount_beds = val; }
        void setBreakfastIncluded(bool val) { breakfast_included = val; }

    protected:
    private:
        int room_nr;
        int amount_beds;
        bool breakfast_included;
};

#endif // ROOM_H
