var gulp  = require('gulp')
var shell = require('gulp-shell')
var watch = require('gulp-watch')

gulp.task('compile', shell.task([
  'clear',
  'make',
]))

gulp.task('watch', function() {
    gulp.watch('./*.c', ['compile']);
    gulp.watch('./*.h', ['compile']);
});

gulp.task('default' ,function() {
    gulp.watch('./*.c', ['compile']);
    gulp.watch('./*.h', ['compile']);
});
