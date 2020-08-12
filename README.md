# Reploid
Reploid is C++ library for load balancing and auto-scaling stateful services. The goal is to build a library for bootstrapping dynamic clusters, taking care of persistence, fault checking, work distribution and data sharing. 

While it is primarily written with the intent of showcasing various architectures and algorithms used with dynamically scaling stateful services, it is functional and can serve as a base when starting to scale applications allowing for easy modification of all functionallities. It also contains configurations specifically for stateless services.<sup>boo</sup>

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

**Client-Server communication**

Let's say that we're making an image-based social media website called Blingstagram. Users can post photos of their fancy jewelry and other users can "like" those photos, which in turn gives the poster Bling. 1 like = 1 Bling. Users can proudly display how much Bling they have on their page and, since the website is obviously ultra popular, we can't store everything on one server. When Alice likes Bob's picture, we want Bob's Bling to go up, even if they are communicating with different servers. In this example, there is no stateful communication, but it serves as an example of the flow.

![](https://github.com/Kaiser-san/Reploid/blob/master/resources/client_server_communication.jpg)

As we can see here, Alice uses the Client to send the like. The Gateway determines, based on the configured algorithm, which Service will communicate with the Client and execute the necessary work. After the Service gets the message from the Client, it can, again based on the configuration, send the information to other Services, so they also have their data updated without doing the work.

Much of this is configurable. We don't have to have multiple service, maybe we want just one. Maybe we don't want to share data between services, instead just have session data be deleted afterwards. Maybe we want to automatically increase the number of our servers based on the number of users. To do this, we make use of the ServerFactory.

**Configuring and starting services**

![](https://github.com/Kaiser-san/Reploid/blob/master/resources/factory_architecture.jpg)

In order to configure our Services, we make a ServerFactory by using a ServerFactoryBuilder. Using a builder pattern allows us to easily add more options. For now we can configure how we make Services, and how we make Gateways. As said before, a Service can be a single server, which has no data sharing. We can make it a cluster that simply talks to a database, and let that layer deal with concurrency. Or we can deal with it ourselves, adding capabilities for data sharing, which data is private, which data is public, how "far" do we have to share data (e.g. players are only visible to each other if they are in the same zone), etc. The same can be said for Gateways, we can make a single gateway, or make a high availability gateway, which is basically a gateway with backups. When we add more servers to the mix, the Gateway is responsible for routing that communication.

**Load balancing**

When talking about load balancing, there are two things to consider. 

The first is how we route new Clients. We can do this in one of 3 ways: Round-robin, Random, and Weighted. Round-robin and Random policies are simple, they don't check the state of the Service, whether it is able to handle more Clients. Weighted is more complex, it takes in many variables, like how many connections a Service already has, how close the Service is to the Client, and many more, to calculate where to route. We may put more weight on availability, since it isn't a real time application, or we may prefer to have less lag, in which case we will choose a fuller, but closer Service.

The second is whether we support sticky (stateful) connections. On surface, this means that when a Client makes a request, we will check if that Client already made a request and connect them to the same Service. However, we have to take into account that a connection is not always of the same intensity, a user may have quick bursts of actions that place stress on the Service and then have periods of inactivity. We have to balance it out, so that a single server doesn't get bombarded at the same time, and to allow for finishing sessions after inactivity.

But sometimes it's not enough, we get more users than we can handle on our servers. So the Gateway can be used to scale up and instatiate more servers.

**Scaling**

Scaling can be Static, Dynamic, and Predictive. 

Static scaling involves a set of time-based rules which the Gateway will follow to instantiate new Services. If we know that most of the users use the app from 18:00 - 24:00, we can increase the number of instances during that time.

Dynamic scaling analyses current usage and instantiates new Services based on need. A lot of services are used worldwide and can't adhere to simple time-based rules. Users come and go, and sometimes we get a larger than usual surge of users. So we can look at server health, latency, used bandwith, etc. to make a descision.

Predictive scaling is similar to dynamic scaling, but rather than base descisions on current data, it extrapolates data from patterns and uses that to scale up before the surge of users comes in. This won't be implemented, as this uses machine-learning (we don't have data for training) and isn't really the focus here. 

**Persistence and data sharing**

If we're storing any data on the Services themselves, then we need to make sure we have backups. We can do this simply, by sending all our data to a few other Services, so in case a Service fails, another Service can ask for those backups from the system. But this will increase our total data usage and bandwith n-fold (for n backups). We can also use more complicated algorithms, such as distribuited RAID, which also solves a bit of security issues, but that brings even more complexity to our solution.

We also have to be able to send current data across Services, like player position, or number of Blings. However, sometimes we can't share our data with everyone. If some players are far away, we don't need to know their location. So all application data can be boxed, and certain rules can be set on sharing those boxes.


# How to Build

Whatever you see is still in progress, so take that in mind. Half of it might not even work. Maybe even none of it.

The project was coded in Visual Studio (on Win10) with Nuget managing the references. Haven't tested it on Unix-based systems, but the underlying libraries all use cross-platform strings and such, so it should be able to build there as well.
