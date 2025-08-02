require 'sinatra'
require 'json'
require_relative './lib/bid_ranker'

set :port, 4567
set :bind, '0.0.0.0'

# Health Check
get '/health' do
  content_type :json
  { status: 'up' }.to_json
end

# Submits a new bid for a contract
post '/bids' do
  content_type :json

  begin
    data = JSON.parse(request.body.read)
    required_fields = %w[contract_id supplier_id amount deadline]
    unless required_fields.all? { |f| data.key?(f) }
      halt 400, { error: 'Missing required fields' }.to_json
    end

    # Simulated storage (in-memory)
    BiddingStore.store_bid(data)
    { message: 'Bid submitted successfully' }.to_json
  rescue => e
    halt 500, { error: e.message }.to_json
  end
end

# Retrieves all bids for a specific contract
get '/bids/:contract_id' do
  content_type :json
  contract_id = params['contract_id']
  bids = BiddingStore.get_bids(contract_id)
  bids.to_json
end

# Ranks bids using the C++ extension
get '/rank/:contract_id' do
  content_type :json
  contract_id = params['contract_id']
  bids = BiddingStore.get_bids(contract_id)

  ranked = BidRanker.rank_bids(bids)
  ranked.to_json
end

# ---------------------------- #
# Simulated Storage Layer     #
# ---------------------------- #
  class BiddingStore
  @bids = {}

  def self.store_bid(bid)
    @bids[bid['contract_id']] ||= []
    @bids[bid['contract_id']] << bid
  end

  def self.get_bids(contract_id)
    @bids[contract_id] || []
  end
end

