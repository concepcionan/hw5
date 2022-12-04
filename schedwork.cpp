

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool scheduleSolve(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    size_t worker
);
bool isValid( 
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    Worker_T workerID
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below
    std::vector<Worker_T> workers;
    for (int i = 0; i < (int)dailyNeed; i++){
        workers.push_back(INVALID_ID);
    }
    for (int i = 0; i < (int)avail.size(); i++){
        sched.push_back(workers);
    }

    return scheduleSolve(avail, dailyNeed, maxShifts, sched, 0, 0);
}

bool scheduleSolve(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    size_t worker
){
    if (day == avail.size() - 1 && worker == dailyNeed) return true;
    if (sched[day][worker] == INVALID_ID){
        for (Worker_T i = 0; i  < avail[day].size(); i++){ 
            sched[day][worker] = i;

            if (isValid(avail, dailyNeed, maxShifts, sched, day, i)){
                if (worker == dailyNeed){
                    if (scheduleSolve(avail, dailyNeed, maxShifts, sched, day+1, 0)) return true;
                }
                else {
                    if (scheduleSolve(avail, dailyNeed, maxShifts, sched, day, worker+1)) return true; 
                }
            }
        }
        sched[day][worker] = INVALID_ID;
    }
    else {
        if (worker == dailyNeed){
            if (scheduleSolve (avail, dailyNeed, maxShifts, sched, day+1, 0)) return true;
        }
        else {
            if (scheduleSolve(avail, dailyNeed, maxShifts, sched, day, worker+1)) return true; 
        }
    }
    return false;
}

bool isValid( 
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    Worker_T workerID
)
{
    if (std::count(sched[day].begin(), sched[day].end(), workerID) > 1) return false;
    size_t shiftCount = 0;
    for (int i = 0; i < (int) avail.size(); i++) {
        shiftCount += std::count(sched[i].begin(), sched[i].end(), workerID);
    }
    return (avail[day][workerID] && shiftCount <= maxShifts);
}