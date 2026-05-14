[00:00:00]  
**Introduction to Data Modeling in System Design Interviews**  
- The video focuses on **data modeling specifically within system design interviews** for software engineers, **not for dedicated data engineering interviews**.  
- It highlights the limited but crucial data modeling knowledge required in system design contexts.  
- Presenter: Evan, a former metastaff engineer and co-founder of Hello Interview, emphasizing interview preparation resources available on the channel and website.

[00:00:45]  
**Definition and Purpose of Data Modeling**  
- Data modeling is the process of defining how an application’s data is:  
  - Structured  
  - Stored  
  - Related  
- Practically, this involves deciding:  
  - What **entities** or **tables** exist  
  - How to **identify or find** these entities  
  - How these entities **connect or relate** to one another  
- The video promises a step-by-step outline of how to do this in system design interviews.

[00:01:12]  
**When to Perform Data Modeling in System Design Interviews**  
- Data modeling usually appears in two phases of the **Hello Interview delivery framework**:  
  1. **Core entities phase** – Define the core entities or nouns (tables) of the system.  
  2. **High-level design phase** – As functional requirements are addressed, data model details such as fields, relationships, and indexes are specified to justify API endpoints and workflows.  
- Example provided: an online auction system with entities like Auction, Item, Bid, User, showing how foreign keys relate these tables during API and functional discussions.

[00:03:27]  
**Choosing the Right Database Type**  
- The choice of database type **strongly influences data modeling**.  
- **Strong advice:** Unless you have extensive experience with other databases, **choose a relational database (PostgreSQL recommended)** for system design interviews.  
- Rationale: Relational databases are the most justifiable and straightforward choice in interviews.  
- Overview of four key database types:  
  - **Relational databases**  
  - **Document databases** (e.g., MongoDB, Firestore)  
  - **Key-value stores**  
  - **Graph databases**  
- *Wide-column databases* are introduced later as they were initially omitted.

[00:05:02]  
**Example: Instagram Data Model Across Different Database Types**  
- Entities: Users, Posts, Likes.

**Relational Database Model:**  
- Three tables: Users, Posts, Likes.  
- Primary keys: Unique IDs for each record.  
- Foreign keys: Posts reference user IDs; Likes reference both user IDs and post IDs.  
- Benefits: Prevent orphaned data, enable complex queries, common in interviews.

**Document Database Model:**  
- Data stored as JSON-like documents with flexible schemas.  
- Possible to embed posts inside user documents or vice versa.  
- Advantage: Schema flexibility, no strict need for joins.  
- Historically less robust join support than relational databases; hence, embedding used to compensate.  
- Main use case: When schema flexibility is needed due to evolving requirements.

**Key Takeaway:**  
- In system design interviews, schema flexibility is rarely required due to narrowly scoped functional requirements.  
- Thus, relational databases typically remain the safer choice.

[00:07:41]  
**Key-Value Stores**  
- Simplest form: data stored as key-value pairs (like a hashmap).  
- Example keys: `user:1`, `post:123`.  
- Extremely fast for exact key lookups but very limited querying capabilities.  
- Typically denormalization-heavy, data duplicated across keys for performance.  
- Common use case: **Caches** (e.g., Redis) placed in front of primary databases for hot data access.  
- Some databases like DynamoDB combine key-value and document features.

[00:11:20]  
**Wide-Column Databases**  
- Characterized by **column families**, where each row can have different columns.  
- Example: User as a row, posts as columns inside a column family, with each post being a separate column.  
- Intended to support **massive write volumes** efficiently by appending new columns rather than updating existing ones.  
- Suitable for: time-series data, event logging, IoT sensor data, analytics workloads.  
- Usually not a go-to choice in interviews unless massive write load is explicit.

[00:13:47]  
**Graph Databases**  
- Data stored as **nodes (entities)** and **edges (relationships)**.  
- Example: Users and Posts as nodes, edges representing "posted" or "liked" relationships.  
- Generally **not recommended in system design interviews** despite seeming appropriate for social networks or recommendation engines.  
- Major social networks like Facebook use relational databases for their social graphs.  
- Advice: Avoid graph databases unless you have deep expertise.

[00:14:45]  
**Introduction to Hello Interview’s Guided Practice Tool**  
- Interactive system design interview practice aligned with the Hello Interview framework.  
- Covers from non-functional requirements to deep dives.  
- Offers real-time feedback and a large, growing library of common system design questions.

[00:15:33]  
**Key Factors to Ground Data Modeling Decisions**  
When designing schema in interviews, base decisions on three critical factors:  
1. **Data Volume**  
   - High volume (millions or billions of users) may require data distribution across multiple systems.  
2. **Access Patterns**  
   - Derived from API queries; determines how data will be retrieved.  
   - Example: News feed queries suggest the need for denormalization or specific indexes.  
3. **Consistency Requirements**  
   - Dictates coupling of data.  
   - Example: Financial transactions require strong consistency, so tightly coupled data storage; user activity feeds can tolerate eventual consistency and be distributed or cached.

[00:17:20]  
**Primary Keys and Foreign Keys**  
- **Primary Key (PK):** Unique identifier for each record (e.g., user ID).  
- **Foreign Key (FK):** A field in one table that references the PK of another table, establishing relationships and enforcing **referential integrity** (prevents orphaned or invalid references).  
- Example: Post table’s user ID FK references Users table’s PK.  
- In interviews, explicitly stating PKs and FKs clarifies relationships and strengthens the design narrative.

[00:19:48]  
**Avoid Overcomplicating Relationship Terminology**  
- Instead of memorizing “one-to-many” or “many-to-many” relationships, focus on:  
  - Defining foreign keys clearly.  
  - Letting relationships emerge naturally from these keys.  
- Example: Likes table containing FKs to both user ID and post ID clearly represents many-to-many relationships without formal terminology.

[00:20:17]  
**Constraints in Database Schema**  
- Constraints enforce correctness at the database level, such as:  
  - **NOT NULL** constraints (columns cannot be empty)  
  - **UNIQUE** constraints (e.g., emails must be unique)  
  - **CHECK** constraints to validate column values  
- These constraints improve data integrity and should be mentioned during interviews for completeness.

[00:21:35]  
**Normalization vs. Denormalization**  

| Concept       | Description                                                                                 | Pros                                   | Cons                                  | Interview Recommendation                           |
|---------------|---------------------------------------------------------------------------------------------|---------------------------------------|---------------------------------------|--------------------------------------------------|
| Normalization | Storing each piece of data in exactly one location (no duplication).                        | Ensures data consistency and avoids anomalies. | Requires joins during queries, potentially slower reads. | Start with normalized design.                      |
| Denormalization | Deliberate duplication of data across tables for performance reasons.                     | Faster reads by avoiding joins.       | Risk of inconsistent data if duplicates are not updated. | Only apply when justified by performance needs.  |

- Denormalization often implemented in a **cache layer** to balance performance and consistency.

[00:23:56]  
**Indexing**  
- Indexes are data structures that enable faster data lookup by avoiding full table scans.  
- Example: B-tree index allows logarithmic time complexity for lookups instead of linear.  
- Index columns based on common query patterns derived from API endpoints.  
- Instagram example indexes:  
  - `user_id` on Posts table for fast retrieval of posts by user.  
  - `post_id` on Comments table for retrieving comments by post.  
- Indexing is generally the **first optimization** before considering denormalization.

[00:26:17]  
**Sharding**  
- Necessary when data volume exceeds the capacity of a single database instance.  
- Data is partitioned across multiple machines (shards) based on a **shard key** or partition strategy.  
- Example: Shard posts by post ID ranges; comments shard along with corresponding posts to avoid cross-shard joins.  
- Key principle:  
  **Shard by your primary access pattern to minimize expensive cross-shard queries.**  
- In interviews, explicitly state your sharding strategy and justify it based on access patterns.

[00:27:40]  
**Summary and Best Practices for Data Modeling in System Design Interviews**  

| Step                     | Description                                                                                       |
|--------------------------|-------------------------------------------------------------------------------------------------|
| 1. Choose Database       | Select the database type (usually relational/PostgreSQL unless you have strong alternative experience). |
| 2. Define Columns        | List columns needed strictly to satisfy functional requirements.                                |
| 3. Specify Keys          | Identify primary keys and foreign keys to enforce uniqueness and relationships.                 |
| 4. Add Indexes           | Add indexes based on API endpoints and query patterns to optimize read operations.              |
| 5. Consider Denormalization | Start normalized; denormalize only if performance cannot be achieved via indexing; typically use a cache for denormalized data. |
| 6. Plan Sharding         | If data volume requires, shard using a partition key aligned with access patterns to avoid cross-shard joins. |

- All of these steps depend on the **three foundational factors**: data volume, access patterns, and consistency requirements.  
- Mastering this approach helps confidently handle the data modeling portion of system design interviews.

[00:30:16]  
**Closing Remarks**  
- Evan encourages viewers to like, subscribe, and comment with requests for future content.  
- The goal is to continue producing helpful, high-quality system design interview preparation videos.  
- Wishes candidates good luck with their upcoming interviews.

---

**Key Insights:**  
- **Relational databases (especially Postgres) are the recommended default choice in system design interviews.**  
- **Data modeling is tightly linked to API design and functional requirements.**  
- **Primary and foreign keys are fundamental tools to define data relationships clearly.**  
- **Normalization should be the starting point; denormalization is an optimization tool, best used sparingly and often via caching.**  
- **Indexing is crucial for efficient data access and should be derived from access patterns.**  
- **Sharding is a design decision driven by scale and must be thoughtfully aligned with access patterns to avoid costly cross-shard queries.**  
- **Avoid overcomplicating relationship terminology; clarity in keys is more important.**  
- **Graph and wide-column databases have niche uses and are generally discouraged in interviews unless justified by specific requirements.**  
- **The entire data modeling process should be grounded in three key factors: data volume, access patterns, and consistency requirements.**
