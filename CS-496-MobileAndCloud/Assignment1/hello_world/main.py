import webapp2
import time


class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/plain'
        localtime = time.asctime(time.localtime(time.time()))
        self.response.write(localtime)


app = webapp2.WSGIApplication([
    ('/', MainPage),
], debug=True)
