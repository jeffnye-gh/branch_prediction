#include "ooo_cpu.h"
#include "tage.h"
#include "loop_pred.h"

#include <ostream>
#include <iostream>
extern std::ostream *tg_os;
using namespace std;

Tage tage_predictor[NUM_CPUS];                      // tage predictor component for each cpu 
LoopPred loop_predictor[NUM_CPUS];                  // loop predictor component for each cpu

int loop_correct[NUM_CPUS] = {0};                   // A counter to decide whose prediction to use
uint8_t tage_pred[NUM_CPUS], loop_pred[NUM_CPUS];   // The predictions of tage and loop predictor

// Updates the counter based on taken/not-taken
void ctr_update (uint8_t taken, uint32_t cpu) {
    if (taken == loop_pred[cpu]) {
        if (loop_correct[cpu] < 127) loop_correct[cpu]++;
    }
    else if (loop_correct[cpu] > -126) loop_correct[cpu]--;
}

// Initialises the predictor
void O3_CPU::initialize_branch_predictor() {
    tage_predictor[cpu].init();
    loop_predictor[cpu].init();
}

// Predicts whether branch is taken or not
uint8_t O3_CPU::predict_branch(uint64_t ip) {
    loop_pred[cpu] = loop_predictor[cpu].get_pred(ip);
    tage_pred[cpu] = tage_predictor[cpu].predict(ip);

(*tg_os)<<"-I: 100"
        <<" pc 0x"<<HEX(8,ip)
        <<" tst_idx "<<DEC<<tst_idx
        <<" lp "<<CAST(loop_pred[cpu])
        <<" tp "<<CAST(tage_pred[cpu]);
++tst_idx;


    if ((loop_predictor[cpu].is_valid) && (loop_correct[cpu] >= 0)) {

(*tg_os)<<" ret->LP"<<endl;

        return loop_pred[cpu];
    }

(*tg_os)<<" ret->TP"<<endl;

    return tage_pred[cpu];
}

// Updates the predictor based on the last branch result
void O3_CPU::last_branch_result(uint64_t ip, uint8_t taken) {
    tage_predictor[cpu].update(ip, taken);
    loop_predictor[cpu].update_entry(taken, tage_pred[cpu]);
    if (loop_predictor[cpu].is_valid && (tage_pred[cpu] != loop_pred[cpu])) ctr_update(taken, cpu);
}
