--------------------------------------------------------------------------------
U.S. Web Design Standards - Drupal Theme SASS Setup
--------------------------------------------------------------------------------

Our SASS set up is based on SMACSS principles, with a little bit of a Drupal
twist.

1. Base
2. Components
3. Layouts
4. Gulp Setup
5. SASS Setup (if you do not want to use Gulp)

--------------------------------------------------------------------------------




--------------------------------------------------------------------------------
1. Base
--------------------------------------------------------------------------------

As part of our Drupal SMACSS system, we commonly store variables, mixins,
functions, iconography, fonts, and Drupal overrides in their own partials that
ultimately make up the "Base" folder. For more detailed documentation, refer to
the SMACSS website:

https://smacss.com/book/type-base




--------------------------------------------------------------------------------
2. Components
--------------------------------------------------------------------------------

Commonly referred to as "modules" we have renamed this to "components" in order
to avoid confusion with the already established Drupal terminology of what a
module is. For more detailed documentation, refer to the SMACSS website:

https://smacss.com/book/type-module




--------------------------------------------------------------------------------
3. Layouts
--------------------------------------------------------------------------------

Layout rules should be split up into partials in this folder in an effort to
separate the infrastructure of the pages from the components that reside in the
various regions. For more detailed documentation, refer to the SMACSS
website:

https://smacss.com/book/type-layout





--------------------------------------------------------------------------------
4. Gulp Setup
--------------------------------------------------------------------------------

The U.S. Web Design Standards theme uses Gulp.js as it's JavaScript task runner.
More information on Gulp.js can be found at http://gulpjs.com.

**You will need to get Gulp.js installed on your system, so stop here if you have
not done so, or go to the next section in the documentation to set up your SASS
files without using Gulp.js.**

To get Gulp up and running in your project you'll want to navigate to the /gulp
folder in your terminal:

$ cd gulp

Once inside the gulp folder, you should see two files, the Gulpfile.js and the
project.json file. Run the following command to install all of the Gulp
dependencies:

$ sudo npm init

Now that all of your dependencies have been installed, you can run the default
Gulp task that watches for SASS/JS changes in our project and then outputs those
changes almost instantly.

$ gulp

That's it! You should see in your terminal that Gulp is now 'watching' your
project for changes. When you save any of the watched files in your project, the
terminal will report everything that is happening, so keep an eye on it to make
sure everything is running smoothly.





--------------------------------------------------------------------------------
5. SASS Setup (if you do not want to use Gulp)
--------------------------------------------------------------------------------

If you've never heard of Gulp.js or you're just not interest in it - don't worry
you can still create and output your SASS the old fashioned way through the
terminal. Remember, you will still have to install SASS itself first:

$ gem install sass

From the root of the theme, run the following command:

$ sass --watch sass/style.scss:css/style.css

What we are doing with that command is "watching" the main SASS file for any
changes. If there is a change to any changes to the file, SASS will process them
to the style.css file which our Drupal installation is looking at.
