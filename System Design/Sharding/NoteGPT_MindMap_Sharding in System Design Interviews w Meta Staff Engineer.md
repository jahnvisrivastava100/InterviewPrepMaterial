# System Design Deep Dive: Sharding

## 🎯 Core Concept and Motivation

Sharding is a fundamental system design technique to scale databases beyond single-machine limits.

Initially, apps start on a single large database, but as storage and write/read throughput demands grow, the database hits capacity ceilings.

Vertical scaling (bigger machines) works temporarily but eventually becomes insufficient.

Sharding splits data horizontally across multiple independent databases (shards), each with separate CPU, memory, and storage.

This allows linear scaling by adding more shards.

## 🧩 Sharding Basics and Strategies

### What to Shard By (Shard Key)

The shard key is the data attribute used to partition data.

#### Good shard keys have:High cardinality: many unique values for even distribution.Even distribution: shards hold roughly equal data and load.Query alignment: shard key matches main query patterns to avoid cross-shard queries.

High cardinality: many unique values for even distribution.

Even distribution: shards hold roughly equal data and load.

Query alignment: shard key matches main query patterns to avoid cross-shard queries.

Examples of good keys: user ID for social apps, order ID for e-commerce.

Bad keys include low-cardinality fields (e.g., boolean flags) or time-based fields causing hotspots.

### How to Distribute Data Across Shards

Range-based sharding: split shard key into fixed ranges; simple but can cause uneven load or hotspots.

Hash-based sharding: hash shard key and mod by number of shards; provides even distribution.

Consistent hashing improves over hash-based by minimizing data reshuffling when shards change.

Directory-based sharding: use a lookup table to map keys to shards; flexible but adds latency and single point of failure.

## ⚠️ Common Challenges and Solutions

### Hotspots and Load Imbalance

Popular keys (e.g., celebrity users) can overload a shard.

#### Solutions:Compound shard keys (adding suffixes) to spread hot keys.Dedicated shards for high-traffic entities (e.g., celebrities).

Compound shard keys (adding suffixes) to spread hot keys.

Dedicated shards for high-traffic entities (e.g., celebrities).

### Cross-Shard Queries

Queries spanning multiple shards are expensive and slow.

#### Mitigations:Choose shard keys aligned with query patterns.Cache expensive cross-shard query results.Denormalize data to reduce cross-shard dependencies.

Choose shard keys aligned with query patterns.

Cache expensive cross-shard query results.

Denormalize data to reduce cross-shard dependencies.

### Consistency and Transactions

Single-shard transactions are straightforward; cross-shard transactions are complex.

Two-phase commit (2PC) ensures atomicity but is slow and fragile.

Saga pattern breaks transactions into steps with compensating actions for failures.

Best practice: avoid cross-shard transactions when possible.

## 💡 Interview Best Practices

Sharding discussion usually arises when addressing scaling non-functional requirements.

Justify sharding need with storage, write, and read throughput calculations.

Propose shard key based on access patterns.

Default to hash-based sharding with consistent hashing unless complexity demands otherwise.

Discuss trade-offs like cross-shard query overhead and plan for future growth.

Use a clear, structured approach covering shard key, distribution method, trade-offs, and scaling strategy.

## 🚀 Additional Resources and Tools

HelloInterview.com offers guided practice tools for system design interviews.

Written breakdowns and deeper dives on concepts like consistent hashing and saga patterns are recommended.

Engaging with these resources helps solidify understanding of sharding and related system design topics.

