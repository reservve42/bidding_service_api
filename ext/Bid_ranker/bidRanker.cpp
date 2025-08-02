#include <ruby.h>
#include <vector>
#include <algorithm>
#include <string>

struct Bid {
    std::string supplier_id;
    double amount;
    int deadline;
};

std::vector<Bid> parse_bids(VALUE bids_array) {
    std::vector<Bid> bids;
    for (long i = 0; i < RARRAY_LEN(bids_array); ++i) {
        VALUE bid = rb_ary_entry(bids_array, i);
        VALUE supplier = rb_hash_aref(bid, rb_str_new_cstr("supplier_id"));
        VALUE amount = rb_hash_aref(bid, rb_str_new_cstr("amount"));
        VALUE deadline = rb_hash_aref(bid, rb_str_new_cstr("deadline"));

        bids.push_back({StringValueCStr(supplier), NUM2DBL(amount), NUM2INT(deadline)});
    }
    return bids;
}

VALUE method_rank_bids(VALUE self, VALUE bids_array) {
    std::vector<Bid> bids = parse_bids(bids_array);
    std::sort(bids.begin(), bids.end(), [](Bid a, Bid b) {
        if (a.amount != b.amount)
            return a.amount < b.amount;
        return a.deadline < b.deadline;
    });

    VALUE ranked = rb_ary_new();
    for (auto &b : bids) {
        VALUE hash = rb_hash_new();
        rb_hash_aset(hash, rb_str_new_cstr("supplier_id"), rb_str_new_cstr(b.supplier_id.c_str()));
        rb_hash_aset(hash, rb_str_new_cstr("amount"), rb_float_new(b.amount));
        rb_hash_aset(hash, rb_str_new_cstr("deadline"), INT2NUM(b.deadline));
        rb_ary_push(ranked, hash);
    }

    return ranked;
}

extern "C" {
    void Init_bid_ranker() {
        VALUE module = rb_define_module("BidRanker");
        rb_define_singleton_method(module, "rank_bids", RUBY_METHOD_FUNC(method_rank_bids), 1);
    }
}
