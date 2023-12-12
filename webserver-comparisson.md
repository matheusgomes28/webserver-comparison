# Comparing Rust/Rocket with C++/Oat++

In this video, we compare C++ and Rust backend
frameworks for web applications. More specifically,
we will look at which language and backend is
better by analysing the following criteria:

- [x] Ease of integration with the language.
- [x] Build times with the entire application and
  dependencies.
- [x] Development activity on the repository.
- [x] Documentation and development time.
- [ ] Performance (requests per second using Drill).
- [ ] Minimal binary size.

## Background and Context

Deciding the best framework to develop a web app
backend can be difficult, specially when there are
so many choices for each language you may prefer.

C++ is not necessarily known for being the most
"backend friendly" language out there, as it has
very few syntactic sugars that make it easy to
achieve common patterns, and you may find yourself
writing a lot more code compared to other languages.

Rust, however, is a modern language with the
promise of safety out of the box. Without a
doubt, Rust is also nicer to write in, and easier
to understand than C++. But will all these
so called "zero-cost" abstractions prove better
than C++
for a simple web-application backend? Let's find out!

## Let's Begin with the Web App Architecture

For this comparrison, I really wanted to focus
mostly on the framework itself. Therefore, the
actual web app's architecture is very simple:
a key/value store with for endpoints:

1. `POST item/{name}/{value}` to store an item with the given name and the value.
2. `GET item/{name}` to get a possible value
stores in our application.
3. `DELETE item/{name}` to delete a value that
was previously stored.
4. `GET items` to show all the items and values
currently stored in the application.

The implementation is also very simple: the main
logic is to manage a thread-safe map that is
storing all of the key/value pairs.

## Moving on to the Choice of Frameworks for Each Language

### Beginning with C++

I was actually surprised as to how many web frameworks
are actually available for C++. After looking at a
few different C++ web framework recommendation articles,
a select few kept popping up:

- Oat++
- Drogon
- Crow
- A few others

The three named frameworks all seem to have a good following
base online. Plus, they all seemed to have fairly active
codebases.

Drogon and Oat++ were the most popular frameworks for C++,
but I was drawn in by Oat++'s recommendations, so I picked that
one.

Oat++ is a lightweight C++ framework for web servers.

It promises to be a highly scalable and resource
efficient tool for the creation of backends for
web applications. All of this with **zero**
dependencies. You heard that right: no dependencies
are needed to build this library. But does it feel like
writing backends for breakfast with Oat++? We'll find out
shortly.

### Similarly, Rust - It's Not Rocket Science

Rust also has quite a few popular web server
frameworks in active development.

- Actix-web
- Hyper (a lower level choice)
- Axum (which uses Hyper internally)
- Rocket (also uses Hyper internally)

Since one of the premises of this video was to
compare the learning curve for a complete beginner
in the framework, I chose Rocket as I already have
experience with Axum.

Rocket has quite a few dependencies itself, and some
of those are quite usefully exported so that you can
use them within the backend,
for example serde for Serialization/Deserialization into
things like Json, Yaml, Toml, etc.

### Now for the First Measure: Development Activity

#### Beginning with Rust & Rocket

Rocket is quite a hot library right now, and the
popularity has exploded like a firework in the past
few years as more and more people started to use Rust.

For a framework first released back in 2016, it still has
the same momentum as a new popular new Rust library.

So basically, I'll give Rocket a 10/10 for
development activity as the Github repository is
blowing up with feature requests, issues recorded,
and PRs to address all these things!

[https://github.com/rwf2/Rocket/graphs/contributors]

#### C++'s Oat++

Surprisingly, Oat++ is actually younger then Rocket. It
was first released back in 2018, making it five years
old at the time of recording this video.

Again, this framework is still very popular among C++
developers. The Github repo also contains a lot of new
issue discussions, feature requests, and PR's implementing
new fixes and features.

Since this library is younger than Rocket, and the number
of contributors and commit frequency is also lower than that
of Rocket, I'll give Oat++ an 8/10 here.

[https://github.com/oatpp/oatpp/graphs/contributors]

### Onto the Second Measure: Integration

#### How Easily Does Rocket Integrate Into Rust Projects?

If you have used Rust before, you know that this
is a trivial step. Rust's Cargo makes it extremely
easy to add third-party libraries to your project
with a simple call to `cargo add`. Rocket is no
different so 10/10 here.

#### In Comparison - Oat++ is a Little More Difficult to Integrate

If you have written C/C++ applications in the past,
you know that including third-party packages feels like
hell sometimes.

Luckily, I used Conan v2 to manage my dependencies here,
and of cource, Oat++ was available in the Conan centre.

[PLUG] If you're interested in learning how Conan can
help you including third party libraries into your C++
projects with a few lines of code, watch this video where
I explain how Conan works in under 30 minutes.

HOWEVER, Since Oat++ is inherently harder to include as C++
does not have a builtin package manager, and I had to include
Conan into my build, I can only give Oat++ an 8/10 here.

### Next Measure: Build Times From a Clean State

Before I get into the nitty gritty of this, I just want
to clarify how I've acquired the data for this section.
To get the average build times, I did a clean build for each
project.

In Rust, this simply means running `cargo clean` and then
timing the `cargo b -r` command. Over and over again.

In C++, this was a little bit harder. We have three stages
to our build here, one of them being the dependency build
with Conan, the other being the CMake configuration, and
the last being the CMake build:

- For the Conan build, I basically told Conan to build
  all dependencies from source, then nuking the Conan
  cache to make sure nothing is lef out of the next
  timed build.
- For the CMake stages, I simply deleted the `build`
  directory for my project. Since I am not using `ccache`
  or anything fancy to cache builds, that should suffice
  on making sure we build from zero every time.

Now, Rocket has a lot of dependencies, so building an
app with Rocket for the first time can take longer
than expected. The average build time for me was about
51.55 seconds. This also includes an outlier run I did
before I started recording with OBS, so the true mean
is likely higher!

C++ blew my mind here. I initially did think it would be
somewhat faster than the Rust build, since Oat++ has
no dependencies. But I also thought that having a separate
package manager to the language would compensate for the
gained build time.

HOWEVER, even when we consider the Conan build time (which
has a bunch of Conan internal calculations), AND the CMake
boilerplate time, we still had a mean build time of 24.13
seconds - Less than half of Rocket's build time. This is even
more impressive when you realise that "fmt" was also included
in the build - a very lightweight library indeed, but likely
added a couple of seconds to the overall build average time.

For this reason, C++ and Oat++ get a 10/10 in this measure.

On the other hand, Rust and Rocket get a disappointing 5/10
here. Why is Rocket's build so slow? Well, I've noticed that
it has too many dependencies. Maybe they could do with curtting
down that number to make the build a little faster. After all,
this is a **tiny** project compared to real-world apps, and it
still takes over two times longer than a not-so-popular C++
framework.

### Looking Into Documentation and Learning Curve

#### Beginning with Rust and Rocket

This is perhaps the criteria where Rust & Rocket
shine the most. The documentation and examples
for Rocket are very complete, and all the quirks
and tricks of this framework are fully documented
somewhere.

As my first time using Rocket to create the
necessary endpoints and handlers, I hardly got
stuck on the implementation. In addition, the Rust
compiler is usually a lot more helpful then C++
compilers, specially when it comes to errors in
macro expansions and templated structures.

The whole app took just under 2 hours to complete. At the
end of the project, it really didn't have that many lines
of code, but this did include research into the framework
and the time for reading the documentation.

Taking these points into account, I can give Rocket a shiny
8/10 here. This may seem a little low, but that's because there
are still areas I believe the documentation could improve. For example,
it was difficult finding out how to return different error types from
the endpoints (such as `Results<json, error>`), so I had to really
dig in their documentation.

#### In Contrast, Oat++ was a Little Bit of an Nightmare

Oat++ does have a shiny documentation page, but it's nowhere near
as useful as Rocket's docs.

For instance, the beginner tutorials are a little fragmented, and
hide a lot of the details that are going to be needed as soon as
you do anything more complex than their "hello world" project.

For example, I struggled to find basic documentation on things like
"adding new endpoints", "passing values to endpoint handlers",
"returning json as the content/type". This is partially to Oat++
having a different architecture to other frameworks, and I wasn't
used to their way of using Controller classes to manage the entire
webserver, component systems to manage resources, and DTO's to manage
responses to users.

I wish they had renamed their doc pages to reflect what the user
may be looking for. Instead of having a "Data Transfer Object" page,
why not call it something like "handling serialisation of responses"
instead?

Also, don't even get me started on the lack of documentation for
multiple macros that, if used properly, make the code a lot easier
to read and develop.

Overall, the Oat++ project took a couple of streams and just over
3.5 hours to complete.

For this reason, I'm sorry but I will give Oat++ a 5/10 here.

