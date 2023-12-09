## Comparing Rust/Rocket with C++/Oat++

In this video, we compare C++ and Rust backend
frameworks for web applications. More specifically,
we will look at which language and backend is
better by analysing the following criteria:

- Ease of integration with the language.
- Build times with the entire application and
  dependencies.
- Development activity on the repository.
- Documentation and development time.
- Performance (requests per second using Drill).
- Minimal binary size.

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
then C++
for a simple web-application backend? Let's find out!

## Web App Architecture

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

## C++ - Writing Backends for Breakfast with Oat++

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
but I was drawn in by Oat++'s recommendations, so I picked that.

Oat++ is a lightweight C++ framework for web servers.

It promises to be a highly scalable and resource
efficient tool for the creation of backends for
web applications. All of this with **zero**
dependencies. You heard that right: no dependencies
are needed to build this library.

## Rust - It's Not Rocket Science

Rust actually has quite a few popular web server
frameworks in active development.

- Actix
- Hyper
- Axum
- Rocket

(Talk about how Hyper is the base for Axum & Rocket)

Since one of the premises of this video was to
compare the learning curve for a complete beginner
in the framework, I chose Rocket as I have
experience with Axum.

Rocket has quite a few dependencies itself, and some
of those are quite usefully exported so the user
can, for example serde for Serialization/Deserialization.

### Development Activity

#### Rust Rocket

Rocket is quite a hot library right now, and the
popularity has exploded like a firework in the past
few years as more and more people use Rust.

So basically, I'll give Rocket a 10/10 for
development activity as the Github repository is
blowing up with feature requests, issues recorded,
and PRs to address all these things!

#### C++'s Oat++


### Integrating Rocket to a Rust Project

If you have used Rust before, you know that this
is a trivial step. Rust's Cargo makes it extremely
easy to add third-party libraries to your project
with a simple call to `cargo add`. Rocket is no
different so 10/10 here.

### Build Times From a Clean State

Rocket has a lot of dependencies, so building an
app with Rocket for the first time can take longer
than expected.

(TODO : actual data and conclusion)

### Documentation and Learning Curve

This is perhaps the criteria where Rust & Rocket
shine the most. The documentation and examples
for Rocket is very complete, and all the quirks
and tricks of this framework are fully documented
somewhere.

As my first time using Rocket to create the
necessary endpoints and handlers, I hardly got
stuck on the implementation. In addition, the Rust
compiler is usually a lot more helpful then C++
compilers, specially when it comes to errors in
macro expansions and templated structures.

