[00:00:00]  
### Introduction to API Design in System Design Interviews  
- Presenter: Evan, former staff engineer at Meta and co-founder of Hello Interview.  
- Target Audience: Candidates preparing for system design or product architecture interviews with an API design focus.  
- Objective: Provide essential API design knowledge sufficient to perform well in interviews without unnecessary complexity.  
- Framework Highlight: Hello Interview delivery framework includes these steps:  
  1. Requirements  
  2. Core Entities  
  3. **API Design** (focus of this video)  
  4. Data Flow  
  5. High-Level Design  
  6. Deep Dives  
- Important note: Spend **no more than 5 minutes** on API design in interviews to avoid failure due to over-detailing.

---

[00:01:11]  
### What is an API?  
- API = Application Programming Interface.  
- Purpose: Enables communication between two software components using defined rules and protocols.  
- Components involved:  
  - Client (e.g., browser or laptop)  
  - Server (machine in a data center)  
  - Database (stores data)  
- Communication is via APIs:  
  - Example: In a Ticketmaster-like system, the client requests a list of events from the server via an API call; the server queries the database via another API call; results flow back to the client.  
- Interview focus: Usually on **external API calls** (client to backend service).

---

[00:02:28]  
### Key Protocols for API Communication in System Design Interviews  
- **REST (Representational State Transfer)**  
  - Default and most common choice (~95% of cases).  
  - Uses standard HTTP methods: GET, POST, DELETE, PUT, PATCH.  
  - Resources represented as URLs.  
- **GraphQL**  
  - Allows clients to request exactly the data needed in a single query, reducing overfetching and underfetching.  
  - More flexible but less commonly required in interviews.  
- **RPC (Remote Procedure Call)**  
  - Used primarily for **internal microservices communication** (server-to-server).  
  - Efficient and lightweight compared to REST.  
- **Real-time Protocols** (Not covered in detail): WebSocket, Server-Sent Events, WebRTC for continuous streaming data (e.g., chat apps).

---

[00:04:09]  
### REST API Design Fundamentals  
- REST is resource-oriented; resources map directly to **core entities** (nouns) identified in requirements.  
- Example core entities for Ticketmaster: Events, Venues, Tickets, Bookings.  
- **Resource Representation:** Resources should be **plural nouns** in URL paths (e.g., `/events`, `/venues`). Do **not** include verbs in URLs (e.g., avoid `/createEvent`). HTTP verbs (GET, POST, etc.) express actions.  
- Interviewers often overlook minor deviations but sticking to plural nouns increases chances of success.  

---

[00:06:00]  
### REST HTTP Methods and Their Usage  
| HTTP Method | Purpose                   | Idempotency                         | Example Use Case                      |
|-------------|---------------------------|-----------------------------------|-------------------------------------|
| GET         | Retrieve data             | Idempotent (multiple requests same outcome) | `GET /events` returns list of events |
| POST        | Create data               | Not idempotent (multiple requests create duplicates) | `POST /events` creates a new event  |
| PUT         | Replace or update entire resource | Idempotent | `PUT /events/123` replaces event 123 data entirely |
| PATCH       | Partial update of resource | Idempotent | `PATCH /events/123` updates specific fields (e.g., date) |
| DELETE      | Delete resource            | Idempotent | `DELETE /events/123` removes event 123 |

- Recommendation: Focus on GET and POST for interviews; PUT and PATCH have niche use cases but knowing distinctions helps.

---

[00:08:52]  
### REST API Input Types  
- **Path Parameters:** Required identifiers within the URL path, e.g., `/events/123` (event ID 123). Used when resource ID is mandatory to fulfill the request.  
- **Query Parameters:** Optional filters appended to the URL, e.g., `/events?city=LosAngeles&date=2024-01-01`. Use question mark for first parameter and ampersand for subsequent ones.  
- **Request Body:** JSON payload for POST, PUT, PATCH requests to create or update resources. Example body for creating an event:  
  ```json
  {
    "title": "Concert",
    "description": "Live concert event",
    "location": "LA",
    "date": "2024-01-01"
  }
  ```

---

[00:11:19]  
### REST API Response Structure and Status Codes  
- Responses include:  
  - **Status Code:** Indicates success or error.  
  - **Response Body:** Data returned, typically JSON.  
- Important HTTP status codes:  
| Status Code | Meaning                   | Usage Context                |
|-------------|---------------------------|-----------------------------|
| 2xx         | Successful requests       | E.g., 200 OK, 201 Created   |
| 4xx         | Client errors             | E.g., 400 Bad Request, 401 Unauthorized, 404 Not Found |
| 5xx         | Server errors             | E.g., 500 Internal Server Error |

- For interviews, grouping status codes into buckets (2xx, 4xx, 5xx) is sufficient.  
- Avoid detailing every field in the response body; refer to core entities instead.

---

[00:13:06]  
### Overview of GraphQL  
- Developed by Facebook in 2012 to address inefficiencies of REST, especially on slow mobile networks.  
- Allows clients to specify exactly which fields to retrieve in one request, avoiding multiple REST calls or overfetching data.  
- Open-sourced in 2015, gaining popularity.  
- Operates over HTTP with a single endpoint accepting a POST request with a query body specifying requested fields.  

---

[00:14:48]  
### GraphQL Query Example and Advantages  
- Single request can fetch nested related data, e.g., event name, date, venue details, ticket availability all at once.  
- Compared to REST, which would require multiple endpoint calls, GraphQL consolidates these into one.  
- Reduces network latency and bandwidth usage by avoiding unnecessary data transfer.

---

[00:15:44]  
### GraphQL Challenges: N+1 Problem and Authorization  
- **N+1 Problem:** Querying a list (e.g., top 100 events) and then querying related data (venues, tickets) for each event leads to many database queries, increasing latency.  
- Solution: Use **batching** or **data loaders** to combine related queries into fewer requests, improving efficiency.  
- **Authorization:** GraphQL allows **field-level authorization**, enabling fine-grained access control (e.g., users can see event name but not revenue). This is enforced by schema resolvers.  
- REST typically secures entire endpoints, not individual fields.

---

[00:17:29]  
### Internal APIs and RPC for Microservices Communication  
- Some interviews, especially backend-heavy ones, focus on **internal service-to-service APIs** rather than client-facing APIs.  
- In such cases, either:  
  - Skip external API design or  
  - Design internal APIs using RPC.  
- **RPC (Remote Procedure Call):**  
  - Modeled as direct method calls on services over the network.  
  - Faster and lighter than REST due to lower overhead (no HTTP headers, status codes, JSON parsing).  
  - Often uses **gRPC** with **protocol buffers**, a compact binary serialization format.  
- Example: Ticket service with RPC methods like `GetEvent`, `CreateBooking`, `GetAvailableTickets`.  

---

[00:19:44]  
### Why Use REST for Client-Server but RPC for Internal Services?  
- REST advantages for clients:  
  - Universal support in browsers, mobile apps, third-party tools.  
  - Passes through firewalls easily.  
  - Human-readable JSON simplifies debugging and adoption.  
- RPC disadvantages externally:  
  - Requires strict protocol agreement on both ends.  
  - Binary formats are not human-readable and need special tooling.  
- RPC ideal for controlled internal environments; REST ideal for diverse external clients.

---

[00:21:58]  
### Common Follow-up Interview Topics: Pagination and Security  
- **Pagination:** Avoid returning large payloads by splitting results into pages.  
  - **Offset-based pagination:** Use query parameters for page number and size, e.g., `?page=1&size=25`. Simple but can cause inconsistencies with concurrent writes.  
  - **Cursor-based pagination:** Use a cursor (e.g., last item ID) to fetch the next set of data, ensuring consistent ordering despite writes. More complex but reliable for dynamic data.  

---

[00:24:52]  
### API Security: Authentication and Authorization  
- Specify which endpoints require authentication (e.g., posting reviews requires a logged-in user).  
- Authentication typically via tokens in HTTP headers:  
  - **JWT (JSON Web Token):** Contains JSON payload with user info (role, expiration) and a cryptographic signature to prevent tampering.  
  - **Session Token:** Simple token used to look up session info on the server.  
- Important security practice: Do **not** rely on user ID submitted in the request body to identify the acting user. Instead, derive user identity from the authenticated token in the header to prevent impersonation.

---

[00:28:07]  
### Practice Resources and Final Advice  
- Hello Interview offers a platform to practice API design questions with personalized, instant feedback across the full system design framework.  
- Candidates appreciate the structured practice flow from requirements through API design to high-level design and deep dives.  
- Final encouragement: Keep API design concise in interviews and focus on key concepts covered here to succeed.

---

### **Key Takeaways:**  
- **REST is the default API style** for client-server communication in interviews; know HTTP methods and resource URL conventions.  
- **GraphQL** offers flexibility but introduces complexity like the N+1 problem; useful to understand but less frequently needed.  
- **RPC/gRPC** excels at internal microservice communication due to efficiency and strong typing.  
- **Pagination and security** are common follow-ups; know offset vs. cursor pagination and the role of JWT/session tokens.  
- Avoid over-detailing API design in interviews; focus on clarity and speed.  
- Practice and feedback improve confidence and performance.
