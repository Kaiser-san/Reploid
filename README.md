# Reploid
Reploid is C++ library for load balancing and auto-scaling stateful services. The goal is to build a library for bootstrapping dynamic clusters, taking care of persistence, fault checking, work distribution and data sharing. 

While it is primarily written with the intent of showcasing various architectures and algorithms used with dynamically scaling stateful services, it is functional and can serve as a base when starting to scale applications allowing for easy modification of all functionallities.

# Why stateful services?
While the overwhelming trend in Service-Oriented Architecture (SOA) is that service statelessness enables easy horizontal scaling and simple load balancing mechanisms, there's a case to be made for stateful services. [A good article by highscalability.com](http://highscalability.com/blog/2015/10/12/making-the-case-for-building-scalable-stateful-services-in-t.html) goes more in depth on the topic, but the TL;DR is that caching user data can severly reduce database costs while optimizing speed at which users access that data. It is very useful in cases where performance is critical, such as video games, but also in applications that would require many transaction messages to be written to the database for communication between requests (e.g. [Uber's Ringpop](https://github.com/uber/ringpop-go)).
>But statelful services require much more maintenance, and backups, and concensus between services and..

They do.
>Isn't that hard?

It is.
>How do we do it?

Very painfully.

Look, I'm not gonna lie and say this is magically gonna make your life easier and run your app 100x faster. But there are cases where we can't achieve statelessness, and I'm looking to make this process as painless as possible. Who knows, maybe this becomes useful some day. <sup> kek, doubt it </sup>

# ReploidApp, ReploidTestService, ReploidTestClient
> I don't care about nerd stuff, I want to look at pretty animations!

Oh boy, do I have something for you! The ReploidApp is a simple GUI app that is designed to simulate clusters of servers with clients sending requests. This is what it looks like:
| NOT YET IMPLEMENTED       | 
| :---:       |
| ![Curved-Straight Edges](https://github.com/cneben/QuickQanava/blob/master/doc/web/docs/images/edges-curved-straight.gif) |

Okay I may have lied about the pretty part...or the animation part... or that it's even works <sup>sue me <sup> pls don't</sup></sup>

The ReploidTestService and ReploidTestClient both have code that serves as an example for how to use the library.
# Alright, how does it work?
**Architecture**

![](https://github.com/Kaiser-san/Reploid/blob/master/resources/reploid_architecture.jpg)

When a Client wants something from a server, it makes a request using the gateway. The gateway then does load balancing and connects the Client to its designated Service. If this is the first time the Client has come to the gateway, then it chooses a free Service instance based on the specified algorithm. Otherwise it connects to the previously used instance. The gateway also does health checks, to see if an instance is still alive and has enough resources to take more Clients. There can be multiple Gateways for a single cluster, ensuring that there is no single point of failure.

**Load balancing**

TBD

**Scaling**

TBD

**Persistence and data sharing**

TBD
