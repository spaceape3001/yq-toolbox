////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/ut.hpp>
#include <basic/DiffEngine.hpp>
#include <basic/Vector.hpp>

namespace ut = boost::ut;
using namespace ut;
using namespace yq;

using svii = std::initializer_list<std::string_view>;

const string_view_vector_t  small0  = string_view_vector_t(svii{ "small"sv });
const string_view_vector_t  small1  = string_view_vector_t(svii{ "small"sv, "small1"sv });

const string_view_vector_t  hobbies3 = string_view_vector_t(svii{
    "3D printing"sv,
    "Acting"sv,
    "Action figure"sv
});

const string_view_vector_t  hobbies3b = string_view_vector_t(svii{
    "Action figure"sv,
    "Aerodynamics"sv, 
    "Aeromodeling"sv
 });


const string_view_vector_t  hobbies5 = string_view_vector_t(svii{
    "3D printing"sv,
    "Acting"sv,
    "Action figure"sv,
    "Aerodynamics"sv, 
    "Aeromodeling"sv
 });

const string_view_vector_t  hobbies7d = string_view_vector_t(svii{
    "3D printing"sv, 
    "Acting"sv, 
    "Action figure"sv, 
    
        // missing two
        
    "Air sports"sv, 
    "Airbrushing"sv, 
    "Aircraft spotting"sv, 
    "Airsoft"sv
});

const string_view_vector_t  hobbies9 = string_view_vector_t(svii{
    "3D printing"sv, 
    "Acting"sv, 
    "Action figure"sv, 
    "Aerodynamics"sv, 
    "Aeromodeling"sv, 
    "Air sports"sv, 
    "Airbrushing"sv, 
    "Aircraft spotting"sv, 
    "Airsoft"sv
});

const string_view_vector_t  hobbiesA = string_view_vector_t(svii{
    "3D printing"sv, 
    "Acting"sv, 
    "Action figure"sv, 
    "Aerodynamics"sv, 
    "Aeromodeling"sv, 
    "Air sports"sv, 
    "Airbrushing"sv, 
    "Aircraft spotting"sv, 
    "Airsoft"sv, 
    "Airsofting"sv, 
    "Amateur Astronomy"sv, 
    "Amateur Radio"sv, 
    "Amateur geology"sv, 
    "American Heritage"sv, 
    "American football"sv, 
    "Animal fancy"sv, 
    "Animals/pets/dogs"sv, 
    "Antiquing"sv, 
    "Antiquities"sv, 
    "Aqua-lung"sv, 
    "Aquarium (Freshwater & Saltwater)"sv, 
    "Archaeology"sv, 
    "Archery"sv, 
    "Architecture"sv, 
    "Art"sv, 
    "Art collecting"sv, 
    "Arts"sv, 
    "Association football"sv, 
    "Astrology"sv, 
    "Astronomy"sv, 
    "Athletics"sv, 
    "Australian rules football"sv, 
    "Auto audiophilia"sv, 
    "Auto racing"sv, 
    "Automotive Maintenance"sv, 
    "Aviation"sv, 
    "BASE jumping"sv, 
    "BMX"sv, 
    "Backgammon"sv, 
    "Backpacking"sv, 
    "Badminton"sv, 
    "Base Jumping"sv, 
    "Baseball"sv, 
    "Basketball"sv, 
    "Basketry"sv, 
    "Baton Twirling"sv, 
    "Beach Volleyball"sv, 
    "Beach/Sun tanning"sv, 
    "Beachcombing"sv, 
    "Beadwork"sv, 
    "Beatboxing"sv, 
    "Becoming A Child Advocate"sv, 
    "Beekeeping"sv, 
    "Bell Ringing"sv, 
    "Belly Dancing"sv, 
    "Bicycle Polo"sv, 
    "Bicycling"sv, 
    "Billiards"sv, 
    "Bird Study"sv, 
    "Bird watching"sv, 
    "Birding"sv, 
    "Birdwatching"sv, 
    "Blacksmithing"sv, 
    "Blogging"sv, 
    "Board games"sv, 
    "Board sports"sv, 
    "BoardGames"sv, 
    "Boating"sv, 
    "Body Building"sv, 
    "Bodybuilding"sv, 
    "Bonsai Tree"sv, 
    "Book collecting"sv, 
    "Book restoration"sv, 
    "Bookbinding"sv, 
    "Boomerangs"sv, 
    "Botany"sv, 
    "Bowling"sv, 
    "Boxing"sv, 
    "Brazilian jiu-jitsu"sv, 
    "Breakdancing"sv, 
    "Brewing Beer"sv, 
    "Bridge (game)"sv, 
    "Bridge Building"sv, 
    "Bringing Food To The Disabled"sv, 
    "Bugling"sv, 
    "Building A House For Habitat For Humanity"sv, 
    "Building Dollhouses"sv, 
    "Bus spotting"sv, 
    "Butterfly Watching"sv, 
    "Button Collecting"sv, 
    "Cabaret"sv, 
    "Cake Decorating"sv, 
    "Calligraphy"sv, 
    "Camping"sv, 
    "Candle Making"sv, 
    "Canoeing"sv, 
    "Car Racing"sv, 
    "Card collecting"sv, 
    "Cartooning"sv, 
    "Casino Gambling"sv, 
    "Cave Diving"sv, 
    "Ceramics"sv, 
    "Cheerleading"sv, 
    "Chemistry"sv, 
    "Chess"sv, 
    "Chicken Raising"sv, 
    "Chicking Call-in Specialist"sv, 
    "Church/church activities"sv, 
    "Cigar Smoking"sv, 
    "Climbing"sv, 
    "Cloud Watching"sv, 
    "Coffee roasting"sv, 
    "Coin Collecting"sv, 
    "Collecting"sv, 
    "Collecting Antiques"sv, 
    "Collecting Artwork"sv, 
    "Collecting Hats"sv, 
    "Collecting Music Albums"sv, 
    "Collecting RPM Records"sv, 
    "Collecting Sports Cards (Baseball, Football, Basketball, Hockey)"sv, 
    "Collecting Swords"sv, 
    "Collection hobbies[edit]"sv, 
    "Color guard"sv, 
    "Coloring"sv, 
    "Comic book collecting"sv, 
    "Community"sv, 
    "Competition hobbies[edit]"sv, 
    "Compose Music"sv, 
    "Computer activities"sv, 
    "Computer programming"sv, 
    "Conworlding"sv, 
    "Cooking"sv, 
    "Corn Husker"sv, 
    "Cosplay"sv, 
    "Cosplaying"sv, 
    "Couponing"sv, 
    "Crafts"sv, 
    "Crafts (unspecified)"sv, 
    "Creative writing"sv, 
    "Cricket"sv, 
    "Crime Prevention"sv, 
    "Crochet"sv, 
    "Crocheting"sv, 
    "Cross-Stitch"sv, 
    "Crossword Puzzles"sv, 
    "Cryptography"sv, 
    "Curling"sv, 
    "Cycling"sv, 
    "Dance"sv, 
    "Dancing"sv, 
    "Darts"sv, 
    "Debate"sv, 
    "Deltiology (postcard collecting)"sv, 
    "Die-cast toy"sv, 
    "Diecast Collectibles"sv, 
    "Digital Photography"sv, 
    "Digital arts"sv, 
    "Disc golf"sv, 
    "Do it yourself"sv, 
    "Dodgeball"sv, 
    "Dog sport"sv, 
    "Dolls"sv, 
    "Dominoes"sv, 
    "Dowsing"sv, 
    "Drama"sv, 
    "Drawing"sv, 
    "Drawing"sv, 
    "Driving"sv, 
    "Dumpster Diving"sv, 
    "Eating out"sv, 
    "Educational Courses"sv, 
    "Electrictiy"sv, 
    "Electronics"sv, 
    "Element collecting"sv, 
    "Embroidery"sv, 
    "Emergency Preparedness"sv, 
    "Entertaining"sv, 
    "Equestrianism"sv, 
    "Exercise (aerobics, weights)"sv, 
    "Exhibition drill"sv, 
    "FIshing"sv, 
    "Falconry"sv, 
    "Fashion"sv, 
    "Fast cars"sv, 
    "Felting"sv, 
    "Fencing"sv, 
    "Field hockey"sv, 
    "Figure skating"sv, 
    "Fire Poi"sv, 
    "Fire Safety"sv, 
    "Fish & Wildlife"sv, 
    "Fishing"sv, 
    "Fishkeeping"sv, 
    "Flag Football"sv, 
    "Floorball"sv, 
    "Floral Arrangements"sv, 
    "Flower arranging"sv, 
    "Flower collecting and pressing"sv, 
    "Fly Fishing"sv, 
    "Fly Tying"sv, 
    "Flying"sv, 
    "Flying disc"sv, 
    "Footbag"sv, 
    "Football"sv, 
    "Foraging"sv, 
    "Foreign language learning"sv, 
    "Fossil hunting"sv, 
    "Four Wheeling"sv, 
    "Freshwater Aquariums"sv, 
    "Frisbee Golf – Frolf"sv, 
    "Gambling"sv, 
    "Game Design"sv, 
    "Games"sv, 
    "Gaming (tabletop games and role-playing games)"sv, 
    "Garage Saleing"sv, 
    "Gardening"sv, 
    "Genealogy"sv, 
    "General Science"sv, 
    "Geocaching"sv, 
    "Geology"sv, 
    "Ghost Hunting"sv, 
    "Glass Sculpting"sv, 
    "Glassblowing"sv, 
    "Glowsticking"sv, 
    "Gnoming"sv, 
    "Go"sv, 
    "Go Kart Racing"sv, 
    "Going to movies"sv, 
    "Golf"sv, 
    "Golfing"sv, 
    "Gongoozling"sv, 
    "Graffiti"sv, 
    "Graphic Arts"sv, 
    "Grip Strength"sv, 
    "Guitar"sv, 
    "Gun Collecting"sv, 
    "Gunsmithing"sv, 
    "Gymnastics"sv, 
    "Gyotaku"sv, 
    "Handball"sv, 
    "Handwriting Analysis"sv, 
    "Hang gliding"sv, 
    "Herping"sv, 
    "Hiking"sv, 
    "Hiking/backpacking"sv, 
    "Hog Calling"sv, 
    "Hog Raising"sv, 
    "Home Brewing"sv, 
    "Home Repair"sv, 
    "Home Theater"sv, 
    "Homebrewing"sv, 
    "Hooping"sv, 
    "Horse riding"sv, 
    "Horseback riding"sv, 
    "Horsemanship"sv, 
    "Hot air ballooning"sv, 
    "Hula Hooping"sv, 
    "Hunting"sv, 
    "Ice hockey"sv, 
    "Ice skating"sv, 
    "Iceskating"sv, 
    "Illusion"sv, 
    "Impersonations"sv, 
    "Indoors[edit]"sv, 
    "Inline skating"sv, 
    "Insect Study"sv, 
    "Insect collecting"sv, 
    "Internet"sv, 
    "Inventing"sv, 
    "Jet Engines"sv, 
    "Jewelry Making"sv, 
    "Jigsaw Puzzles"sv, 
    "Jogging"sv, 
    "Journalism"sv, 
    "Judo"sv, 
    "Juggling"sv, 
    "Jukskei"sv, 
    "Jump Roping"sv, 
    "Kabaddi"sv, 
    "Kart racing"sv, 
    "Kayaking"sv, 
    "Keep A Journal"sv, 
    "Kitchen Chemistry"sv, 
    "Kite Boarding"sv, 
    "Kite flying"sv, 
    "Kites"sv, 
    "Kitesurfing"sv, 
    "Knapping"sv, 
    "Knife making"sv, 
    "Knife throwing"sv, 
    "Knitting"sv, 
    "Knotting"sv, 
    "Kombucha Brewing"sv, 
    "LARPing"sv, 
    "Lacemaking"sv, 
    "Lacrosse"sv, 
    "Landscaping"sv, 
    "Lapidary"sv, 
    "Laser tag"sv, 
    "Lasers"sv, 
    "Law"sv, 
    "Lawn Darts"sv, 
    "Learn to Play Poker"sv, 
    "Learning"sv, 
    "Learning A Foreign Language"sv, 
    "Learning An Instrument"sv, 
    "Learning To Pilot A Plane"sv, 
    "Leathercrafting"sv, 
    "Leatherworking"sv, 
    "Lego building"sv, 
    "Legos"sv, 
    "Letterboxing"sv, 
    "Listening to music"sv, 
    "Lockpicking"sv, 
    "Locksport"sv, 
    "Machining"sv, 
    "Macramé"sv, 
    "Magic"sv, 
    "Mahjong"sv, 
    "Making Model Cars"sv, 
    "Marbles"sv, 
    "Marksmanship"sv, 
    "Martial Arts"sv, 
    "Masonry"sv, 
    "Matchstick Modeling"sv, 
    "Medicine"sv, 
    "Meditation"sv, 
    "Metal Detecting"sv, 
    "Metallurgy"sv, 
    "Metalworking"sv, 
    "Meteorology"sv, 
    "Microscopy"sv, 
    "Mineral collecting"sv, 
    "Model Aircraft"sv, 
    "Model Building"sv, 
    "Model Design & Building"sv, 
    "Model Design"sv, 
    "Model Railroading"sv, 
    "Model Rockets"sv, 
    "Modeling Ships"sv, 
    "Models"sv, 
    "Motor sports"sv, 
    "Motorboating"sv, 
    "Motorcycles"sv, 
    "Mountain Biking"sv, 
    "Mountain Climbing"sv, 
    "Mountain biking"sv, 
    "Mountaineering"sv, 
    "Movie Making"sv, 
    "Movie and movie memorabilia collecting"sv, 
    "Mushroom hunting/Mycology"sv, 
    "Music"sv, 
    "Musical Instruments"sv, 
    "Nail Art"sv, 
    "Native American Culture (Lore)"sv, 
    "Nature"sv, 
    "Needlepoint"sv, 
    "Netball"sv, 
    "Nordic skating"sv, 
    "Nuclear Science"sv, 
    "Observation hobbies[edit]"sv, 
    "Oceanography"sv, 
    "Orienteering"sv, 
    "Origami"sv, 
    "Outdoors[edit]"sv, 
    "Owning An Antique Car"sv, 
    "PVC Bows"sv, 
    "Paintball"sv, 
    "Painting"sv, 
    "Papermache"sv, 
    "Papermaking"sv, 
    "Parachuting"sv, 
    "Paragliding or Power Paragliding"sv, 
    "Parkour"sv, 
    "People Watching"sv, 
    "Personal Fitness"sv, 
    "Pets"sv, 
    "Petsitting"sv, 
    "Photography"sv, 
    "Piano"sv, 
    "Pigeon racing"sv, 
    "Pinochle"sv, 
    "Pioneering"sv, 
    "Pipe Smoking"sv, 
    "Planking"sv, 
    "Playing music"sv, 
    "Playing musical instruments"sv, 
    "Playing team sports"sv, 
    "Plumbing"sv, 
    "Poi"sv, 
    "Poker"sv, 
    "Pole Dancing"sv, 
    "Polo"sv, 
    "Pottery"sv, 
    "Powerboking"sv, 
    "Programming"sv, 
    "Protesting"sv, 
    "Public Speaking"sv, 
    "Puppetry"sv, 
    "Puzzles"sv, 
    "Pyrotechnics"sv, 
    "Quilting"sv, 
    "R/C Boats"sv, 
    "R/C Cars"sv, 
    "R/C Helicopters"sv, 
    "R/C Planes"sv, 
    "Rabbit Raising"sv, 
    "Racing Pigeons"sv, 
    "Racquetball"sv, 
    "Radio-controlled car racing"sv, 
    "Rafting"sv, 
    "Railfans"sv, 
    "Railroading"sv, 
    "Rappelling"sv, 
    "Rapping"sv, 
    "Reading"sv, 
    "Reading To The Elderly"sv, 
    "Record collecting"sv, 
    "Relaxing"sv, 
    "Renaissance Faire"sv, 
    "Renting movies"sv, 
    "Reptiles"sv, 
    "Rescuing Abused Or Abandoned Animals"sv, 
    "Rifle Shooting"sv, 
    "Robotics"sv, 
    "Rock Balancing"sv, 
    "Rock Climbing"sv, 
    "Rock Collecting"sv, 
    "Rockets"sv, 
    "Rocking AIDS Babies"sv, 
    "Roleplaying"sv, 
    "Roller derby"sv, 
    "Roller skating"sv, 
    "Rowing"sv, 
    "Rugby"sv, 
    "Rugby league football"sv, 
    "Running"sv, 
    "Sailing"sv, 
    "Salesmanship"sv, 
    "Saltwater Aquariums"sv, 
    "Sand Castles"sv, 
    "Sand art"sv, 
    "Scholarship"sv, 
    "Scouting"sv, 
    "Scrapbooking"sv, 
    "Scuba Diving"sv, 
    "Sculling or Rowing"sv, 
    "Sculpting"sv, 
    "Sculpture"sv, 
    "Sea glass collecting"sv, 
    "Search and Rescue"sv, 
    "Seashell collecting"sv, 
    "Self Defense"sv, 
    "Sewing"sv, 
    "Shark Fishing"sv, 
    "Sheep Farming"sv, 
    "Shooting"sv, 
    "Shooting (Sports)"sv, 
    "Shopping"sv, 
    "Shortwave listening"sv, 
    "Shotgun Shooting"sv, 
    "Singing"sv, 
    "Singing In Choir"sv, 
    "Skateboarding"sv, 
    "Skating"sv, 
    "Skeet Shooting"sv, 
    "Sketching"sv, 
    "Skiing"sv, 
    "Skimboarding"sv, 
    "Sky Diving"sv, 
    "Slacklining (like tightrope, but with flat webbing)"sv, 
    "Sleeping"sv, 
    "Slingshots"sv, 
    "Slot Car Racing"sv, 
    "Small-boat sailing"sv, 
    "Snorkeling"sv, 
    "Snow Sports"sv, 
    "Snowboarding"sv, 
    "Soap Making"sv, 
    "Soccer"sv, 
    "Socializing with friends/neighbors"sv, 
    "Space Exploration"sv, 
    "Speed Cubing (rubix cube)"sv, 
    "Speed skating"sv, 
    "Spelunkering"sv, 
    "Spending time with family/kids"sv, 
    "Sports"sv, 
    "Squash"sv, 
    "Stamp Collecting"sv, 
    "Stand-up comedy"sv, 
    "Stone collecting"sv, 
    "Stone skipping"sv, 
    "Storm Chasing"sv, 
    "Storytelling"sv, 
    "String Figures"sv, 
    "Sudoku"sv, 
    "Surf Fishing"sv, 
    "Surfing"sv, 
    "Survival"sv, 
    "Swimming"sv, 
    "TV watching"sv, 
    "Table football"sv, 
    "Table tennis"sv, 
    "Taekwondo"sv, 
    "Tai chi"sv, 
    "Tatting"sv, 
    "Taxidermy"sv, 
    "Tea Tasting"sv, 
    "Tennis"sv, 
    "Tesla Coils"sv, 
    "Tetris"sv, 
    "Textiles"sv, 
    "Texting"sv, 
    "Theatres"sv, 
    "Tombstone Rubbing"sv, 
    "Tool Collecting"sv, 
    "Topiary"sv, 
    "Tour skating"sv, 
    "Toy Collecting"sv, 
    "Train Collecting"sv, 
    "Train Spotting"sv, 
    "Traveling"sv, 
    "Treasure Hunting"sv, 
    "Trekkie"sv, 
    "Triathlon"sv, 
    "Trucks"sv, 
    "Tutoring Children"sv, 
    "Ultimate Disc "sv, 
    "Ultimate Frisbee"sv, 
    "Urban Exploration"sv, 
    "Vacation"sv, 
    "Vehicle restoration"sv, 
    "Video Games"sv, 
    "Video game collecting"sv, 
    "Videophilia"sv, 
    "Vintage cars"sv, 
    "Violin"sv, 
    "Volleyball"sv, 
    "Volunteer"sv, 
    "Walking"sv, 
    "Warhammer"sv, 
    "Watching movies"sv, 
    "Watching sporting events"sv, 
    "Water Sports"sv, 
    "Waterskiing"sv, 
    "Weather"sv, 
    "Weather Watcher"sv, 
    "Web surfing"sv, 
    "Weightlifting"sv, 
    "Welding"sv, 
    "Whale Watching"sv, 
    "Whitewater"sv, 
    "Whittling"sv, 
    "Wilderness Survival"sv, 
    "Windsurfing"sv, 
    "Wine Making"sv, 
    "Wingsuit Flying"sv, 
    "Wood Carving"sv, 
    "Woodwork"sv, 
    "Woodworking"sv, 
    "Working In A Food Pantry"sv, 
    "Working on cars"sv, 
    "World Record Breaking"sv, 
    "Worldbuilding"sv, 
    "Wrestling"sv, 
    "Writing"sv, 
    "Writing Music"sv, 
    "Writing Songs"sv, 
    "Yo-yoing"sv, 
    "YoYo"sv, 
    "Yoga"sv, 
    "Ziplining"sv, 
    "Zumba"sv
});

struct Trace {
    yq::diff::Edit      type;
    uint64_t            cnt = 0;
    
    bool    equiv(const yq::diff::edit_t& r)    const
    {
        return (r.type == type) && (r.cnt == cnt);
    }
};

Trace operator"" _eq(unsigned long long i)
{
    return Trace{ yq::diff::Edit::Same, i };
}

Trace operator"" _a(unsigned long long i)
{
    return Trace{ yq::diff::Edit::Add, i };
}

Trace operator"" _r(unsigned long long i)
{
    return Trace{ yq::diff::Edit::Remove, i };
}

bool    equivalent(const std::vector<yq::diff::edit_t>& vec, std::initializer_list<Trace> ops)
{
    if(vec.size() != ops.size())    
        return false;
        
    auto i = vec.begin();
    auto j = ops.begin();
    for(; (i != vec.end()) && (j != ops.end()); ++i, ++j)
        if(!j->equiv(*i))
            return false;
    return true;
}



ut::suite tests = []{

    "same middle snake"_test = []{
        expect( diff::match_t{ { 0, 3 }, { 0, 3 }, 0 } == diff::middle_snake(hobbies3, hobbies3 ));
        expect( diff::match_t{ { 0, 5 }, { 0, 5 }, 0 } == diff::middle_snake(hobbies5, hobbies5 ));
        expect( diff::match_t{ { 0, 9 }, { 0, 9 }, 0 } == diff::middle_snake(hobbies9, hobbies9 ));
    };

    "end insert middle snake"_test = []{
        expect( diff::match_t{ { 3, 3 }, { 4, 4}, 2 } == diff::middle_snake(hobbies3, hobbies5 ) );
    };

    "end delete middle snake"_test = []{
        expect( diff::match_t{ { 4, 4 }, { 3, 3}, 2 } == diff::middle_snake(hobbies5, hobbies3 ) );
    };
    
    "middle insert middle snake"_test = []{
        expect( diff::match_t{ { 3, 3 }, { 4, 4}, 2 } == diff::middle_snake(hobbies7d, hobbies9) );
    };

    "middle remove middle snake"_test = []{
        expect( diff::match_t{ { 4, 4 }, { 3, 3}, 2 } == diff::middle_snake(hobbies9, hobbies7d) );
    };

    "same compare"_test = []{
        expect( true == equivalent(diff::consolidate(diff::compare(small0, small0)), { 1_eq } ));
        expect( true == equivalent(diff::consolidate(diff::compare(hobbies3, hobbies3)), { 3_eq } ));
        expect( true == equivalent(diff::consolidate(diff::compare(hobbies9, hobbies9)), { 9_eq } ));
        expect( true == equivalent(diff::consolidate(diff::compare(hobbiesA, hobbiesA)), { 573_eq } ));
    };
    
    "end insert compare"_test = []{
        expect( true == equivalent(diff::consolidate(diff::compare(hobbies3, hobbies5)), { 3_eq, 2_a } ));
    };

    "end delete compare"_test = []{
        expect( true == equivalent(diff::consolidate(diff::compare(hobbies5, hobbies3)), { 3_eq, 2_r } ));
    };
    
    "move compare"_test = []{
        expect( true == equivalent(diff::consolidate(diff::compare(hobbies3, hobbies3b)), { 2_r, 1_eq, 2_a } ));
    };
    
    "begin insert compare"_test = []{
        expect( true == equivalent(diff::consolidate(diff::compare(hobbies3b, hobbies5)), { 2_a, 3_eq } ));
    };

    "begin delete compare"_test = []{
        expect( true == equivalent(diff::consolidate(diff::compare(hobbies5, hobbies3b)), { 2_r, 3_eq } ));
    };
    
    "middle insert compare"_test = []{
        expect( true == equivalent(diff::consolidate(diff::compare(hobbies7d, hobbies9)), { 3_eq, 2_a, 4_eq } ));
    };

    "middle delete compare"_test = []{
        expect( true == equivalent(diff::consolidate(diff::compare(hobbies9, hobbies7d)), { 3_eq, 2_r, 4_eq } ));
    };
};


int main(){
    log_to_std_output();
    return ut::cfg<>.run();
};

