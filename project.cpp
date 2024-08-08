#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
double EXTRA_CHARGE_RATE = 0.05;  // rupees per watt for consumption above 15,000 watts (15 kW)

class ChargingBuilding {
public:
    class ChargingPoint {
    public:
        ChargingPoint() : total_wattage(0) {}

        void set_usage(int usage) {
            total_wattage = usage;
            p_u.push_back(usage); // add the total power usage to the vector
        }

        // Add a method to calculate the total power consumption of the charging point in watts
        int get_total_power_consumption() {
            int total = 0;
            for (int usage : p_u) {
                total += usage; // add the power usage for each day
            }
            return total;
        }

        // Add a method to calculate the extra charge for the charging point if the power consumption exceeds 15,000 watts
        double get_extra_charge() {
            int power = get_total_power_consumption();
            if (power > 5000) {
                return (power - 5000) * EXTRA_CHARGE_RATE; // charge for the extra power above 15,000 watts
            } else {
                return 0; // no extra charge
            }
        }

        // Add a method to print the output for the charging point
        void print_output() {
           int   charge_rent=500;
            cout << "Units consumed: " << get_total_power_consumption() << " watts" << endl; // print the power consumption
            cout << "Extra amount needed to pay: " << get_extra_charge() << " Rs" << endl; // print the extra charge
            if( get_extra_charge()!=0)
            {
                cout<<"Total amount charged: "<<charge_rent+  get_extra_charge()<<"Rs"<<endl;
            }
            else{
                 cout<<"Total amount charged: "<<  get_extra_charge()<<"Rs"<<endl;
            }
            
            cout << endl; // leave a blank line
        }

    private:
        vector<int> p_u; // vector to store the power usage in watts for each day
        int total_wattage; // total power consumption of the charging point
    };

    class ChargingStation {
    private:
        vector<ChargingPoint> points; // change to a vector of charging points to allow multiple points per station

    public:
        ChargingStation(int num_points) {
            for (int i = 0; i < num_points; ++i) {
                points.push_back(ChargingPoint()); // create a charging point
            }
        }

        void set_point_usage(int point_index, int power_usage) {
            points[point_index].set_usage(power_usage); // set the usage for the given charging point
        }

        // Add a method to calculate the total power consumption of the station in watts
        int get_total_power_consumption() {
            int power = 0;
            for (ChargingPoint &point : points) {
                power += point.get_total_power_consumption();
            }
            return power;
        }

        // Add a method to calculate the total extra charge for the station
        double get_total_extra_charge() {
            double charge = 0;
            for (ChargingPoint &point : points) {
                charge += point.get_extra_charge();
            }
            return charge;
        }

        // Add a method to print the output for each charging point in the station
        void print_output() {
            for (int i = 0; i < points.size(); ++i) {
                cout << "Charging Point no: " << i + 1 << endl; // charging point number starts from 1
                points[i].print_output(); // print the output for the charging point
            }
        }
    };

    ChargingBuilding(int num_stations, int num_points_per_station) {
        for (int i = 0; i < num_stations; ++i) {
            stations.push_back(ChargingStation(num_points_per_station)); // create a station with the given number of points
        }
    }

    void set_point_usage(int station_index, int point_index, int power_usage) {
        stations[station_index].set_point_usage(point_index, power_usage); // set the usage for the given charging point in the given station
    }

    // Add a method to calculate the total power consumption of the building in watts
    int get_total_power_consumption() {
        int power = 0;
        for (ChargingStation &station : stations) {
            power += station.get_total_power_consumption();
        }
        return power;
    }

    // Add a method to calculate the total extra charge for the building
    double get_total_extra_charge() {
        double charge = 0;
        for (ChargingStation &station : stations) {
            charge += station.get_total_extra_charge();
        }
        return charge;
    }

    // Add a method to print the output for each station in the building
    void print_output() {
        for (int i = 0; i < stations.size(); ++i) {
            cout << "Charging Station no: " << i + 1 << endl; // charging station number starts from 1
            stations[i].print_output(); // print the output for each charging point in the station
        }
    }

private:
    vector<ChargingStation> stations;
};

int main() {
  
    fstream inputFile;
   inputFile.open ("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Unable to open the input file." << endl;
        return 1;
    }

    int num_stations, num_points_per_station;
    inputFile >> num_stations >> num_points_per_station; // read the number of stations and points per station from the input file

    ChargingBuilding chargingBlock(num_stations, num_points_per_station); // create the charging building object with the given data

    for (int i = 0; i < num_stations; ++i) {
        for (int j = 0; j < num_points_per_station; ++j) {
            int power_usage; // read the power usage in watts for the charging point
            inputFile >> power_usage;
            chargingBlock.set_point_usage(i, j, power_usage); // set the usage for the charging point in the station
        }
    }

    cout << "Total units consumed: " << chargingBlock.get_total_power_consumption() << " watts" << endl; // print the total power consumption of the building
    cout << "Total extra charge: " << chargingBlock.get_total_extra_charge() << " Rs" << endl; // print the total extra charge for the building
    fstream file;
    file.open("payment.txt",ios::app);

    if(file.is_open())
    {   
        file<<"additional amount collected   "<<chargingBlock.get_total_extra_charge()<<endl;
    }
    else{
        cout<<"Unable to open the output file. ";
    }
    cout << endl; // leave a blank line
    chargingBlock.print_output(); // print the output for each station and charging point in the building

    return 0;
}