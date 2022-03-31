#include<iostream>
#include<math.h>
#include<SFML\Graphics.hpp>
#include<complex>
#include<thread>
#include<vector>
#include<list>
#include<map>

using namespace std;

complex<double> f(complex<double> x) {
	return pow(x, 8) + (real(3) * pow(x,4)) - real(4);
	//return pow(x, 3) - real(1);
}

complex<double> df(complex<double> x) {
	return (real(8) * pow(x, 7)) + (real(12) * pow(x, 2));
	//return real(3) * pow(x, 2);
}

complex<double> newtonsMethod(complex<double> guess, int depth) {
	if (depth == 0) {
		return guess;
	}
	return newtonsMethod((guess - (f(guess) / df(guess))), depth - 1);
}

double distance(complex<double> pos1, complex<double> pos2) {
	return (pow(pos2.real() - pos1.real(), 2) + pow(pos2.imag() - pos1.imag(), 2));
}

bool in(list<pair<double, double>> roots, pair<double, double> searchVal) {
	for (auto& root : roots) {
		//cout << "comparing " << root.first << ", " << root.second << " to " << searchVal.first << ", " << searchVal.second << endl;
		if (root == searchVal) {
			//cout << root.first << ", " << root.second << " == " << searchVal.first << ", " << searchVal.second << endl;
			return true;
		}
	}
	return false;
}



void fill_array(sf::VertexArray& set, float scale, float width, float height, sf::Vector2f mouse, sf::Vector2f &last_shift, long double &last_scale, int thread, int max_threads) {
	sf::Vector2f shift;
	long double horizontalStart;
	long double horizontalEnd;
	long double verticalStart;
	long double verticalEnd;
	sf::Vector2f origin((width / 2), (height / 2));
	long double scaleStart = (-2 / scale);
	long double scaleEnd = (2 / scale);
	long double horizontalSize = (width / (abs(scaleStart) + abs(scaleEnd)));
	long double verticalSize = (height / (abs(scaleStart) + abs(scaleEnd)));
	long double horizontalRes = (abs(scaleStart) + abs(scaleEnd)) / width * 1;
	long double verticalRes = (abs(scaleStart) + abs(scaleEnd)) / height * 1;
	//cout << scale << endl;

	shift = origin + ((origin - mouse) * scale);

	horizontalStart = scaleStart + ((origin.x - shift.x) / horizontalSize);
	horizontalEnd = scaleEnd + ((origin.x - shift.x) / horizontalSize);
	verticalStart = scaleStart + ((origin.y - shift.y) / verticalSize);
	verticalEnd = scaleEnd + ((origin.y - shift.y) / verticalSize);

	sf::Vector2f position;
	/*complex<double> root1(1, 0);
	complex<double> root2(-.5, -.866025);
	complex<double> root3(-.5, .866025);*/
	complex<double> root1(1, 0);
	complex<double> root2(-1, 0);
	complex<double> root3(1, 1);
	complex<double> root4(1, -1);
	complex<double> root5(0, 1);
	complex<double> root6(0, -1);
	complex<double> root7(-1, 1);
	complex<double> root8(-1, -1);
	double distanceToP1;
	double distanceToP2;
	double distanceToP3;
	double distanceToP4;
	double distanceToP5;
	double distanceToP6;
	double distanceToP7;
	double distanceToP8;
	complex<double> num;
	map<pair<double,double>, int> rootsearch;
	for (long double t = horizontalStart; t < horizontalEnd; t += horizontalRes) {

		for (long double m = verticalStart; m < verticalEnd; m += verticalRes) {

			position = sf::Vector2f(t * horizontalSize, m * verticalSize) + shift;

			if (position.x >= 0 and position.x <= width and position.y >= 0 and position.y <= height) {

				if (position.x >= ((width / max_threads) * thread) and position.x <= ((width / max_threads) * (thread + 1))) {

					complex<double> c(t, m);

					num = newtonsMethod(c, 30);
					
					//rootsearch.insert({{ num.real(), num.imag() }, 0});

					distanceToP1 = distance(num, root1);
					distanceToP2 = distance(num, root2);
					distanceToP3 = distance(num, root3);
					distanceToP4 = distance(num, root4);
					distanceToP5 = distance(num, root5);
					distanceToP6 = distance(num, root6);
					distanceToP7 = distance(num, root7);
					distanceToP8 = distance(num, root8);

					set.append(sf::Vertex(position, sf::Color(num.imag() * 6, num.imag() * 8, num.imag() * 12)));

					if (distanceToP1 == min({ distanceToP1, distanceToP2, distanceToP3, distanceToP4, distanceToP5, distanceToP6, distanceToP7, distanceToP8 })) {
						set.append(sf::Vertex(position, sf::Color::Blue));
					}
					else if (distanceToP2 == min({ distanceToP1, distanceToP2, distanceToP3, distanceToP4, distanceToP5, distanceToP6, distanceToP7, distanceToP8 })) {
						set.append(sf::Vertex(position, sf::Color::Cyan));
					}
					else if (distanceToP3 == min({ distanceToP1, distanceToP2, distanceToP3, distanceToP4, distanceToP5, distanceToP6, distanceToP7, distanceToP8 })) {
						set.append(sf::Vertex(position, sf::Color::Green));
					}
					else if (distanceToP4 == min({ distanceToP1, distanceToP2, distanceToP3, distanceToP4, distanceToP5, distanceToP6, distanceToP7, distanceToP8 })) {
						set.append(sf::Vertex(position, sf::Color::Magenta));
					}
					else if (distanceToP5 == min({ distanceToP1, distanceToP2, distanceToP3, distanceToP4, distanceToP5, distanceToP6, distanceToP7, distanceToP8 })) {
						set.append(sf::Vertex(position, sf::Color::Red));
					}
					else if (distanceToP6 == min({ distanceToP1, distanceToP2, distanceToP3, distanceToP4, distanceToP5, distanceToP6, distanceToP7, distanceToP8 })) {
						set.append(sf::Vertex(position, sf::Color::Yellow));
					}
					else if (distanceToP7 == min({ distanceToP1, distanceToP2, distanceToP3, distanceToP4, distanceToP5, distanceToP6, distanceToP7, distanceToP8 })) {
						set.append(sf::Vertex(position, sf::Color(89, 130, 52)));
					}
					else if (distanceToP8 == min({ distanceToP1, distanceToP2, distanceToP3, distanceToP4, distanceToP5, distanceToP6, distanceToP7, distanceToP8 })) {
						set.append(sf::Vertex(position, sf::Color(173, 189, 56)));
					}
					
					/*if (distanceToP1 < distanceToP2 and distanceToP1 < distanceToP3) {
						set.append(sf::Vertex(position, sf::Color(104, 129, 157)));
					}
					else if (distanceToP2 < distanceToP1 and distanceToP2 < distanceToP3) {
						set.append(sf::Vertex(position, sf::Color(173, 189, 56)));
					}
					else if (distanceToP3 < distanceToP2 and distanceToP3 < distanceToP1) {
						set.append(sf::Vertex(position, sf::Color(89, 130, 52)));
					}*/
				}
			}
		}
	}
	list<pair<double, double>> roots;
	/*for (auto& x : rootsearch) {
		if (not in(roots, x.first)) {
			roots.push_back(x.first);
		}
	}
	for (auto& r : roots) {
		cout << r.first << ", " << r.second << endl;
	}
	cout << endl;*/
}

void make_set(list<sf::VertexArray>& sets, list<sf::VertexArray>::iterator setIter, list<thread>& active_threads, int max_threads, long double scale, int window_width, int window_height, sf::Vector2f mouse, sf::Vector2f& last_shift, long double& last_scale) {
	int i = 0;
	for (setIter = sets.begin(); setIter != sets.end(); setIter++) {
		(*setIter).clear();
	}
	for (auto& s : sets) {
		active_threads.emplace_back(fill_array, ref(s), scale, window_width, window_height, mouse, ref(last_shift), ref(last_scale), i, max_threads);
		i++;
	}
}

int main() {
	//RENDER SETUP----------------------------------------------------------
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Newtons Fractal", sf::Style::None);
	window.setPosition(sf::Vector2i(460, 20));
	window.setFramerateLimit(60);

	//VARIABLES-------------------------------------------------------------
	sf::Color bgColor = sf::Color(8, 6, 12);
	long double scale = 1;
	sf::Vector2f last_shift;
	long double last_scale = 0;
	sf::Event event;
	list<thread> active_threads;
	int max_threads = 12;
	list<sf::VertexArray> sets;
	list<sf::VertexArray>::iterator setIter;
	//sf::CircleShape dot(1);
	//dot.setFillColor(sf::Color::Green);
	//dot.setPosition(500, 500);
	////
	//sf::CircleShape root1(10);
	//root1.setFillColor(sf::Color::Green);
	//root1.setPosition(750, 500);
	////
	//sf::CircleShape root2(10);
	//root2.setFillColor(sf::Color::Green);
	//root2.setPosition((-.5 * 250) + 500, (-.866025 * 250) + 500);
	////
	//sf::CircleShape root3(10);
	//root3.setFillColor(sf::Color::Green);
	//root3.setPosition((-.5 * 250) + 500, (.866025 * 250) + 500);
	////
	int totalPoints = 0;

	//INITIAL SET CREATION---------------------------------------------------
	for (int i = 0; i < max_threads; i++) {
		sf::VertexArray s1;
		s1.setPrimitiveType(sf::PrimitiveType::Points);
		sets.push_back(s1);
	}
	make_set(sets, setIter, active_threads, max_threads, scale, window.getSize().x, window.getSize().y, sf::Vector2f(500,500), last_shift, last_scale);

	//GAME LOOP--------------------------------------------------------------
	while (window.isOpen()) {
		while (window.pollEvent(event))
		{
			// Close window: exit--------------------------------------------------------------------------------------------------------------------------
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
				window.close();
			}

			if (event.type == sf::Event::MouseWheelScrolled) {
				if (event.mouseWheelScroll.delta > 0) {
					scale *= 2;
				}
				else if (event.mouseWheelScroll.delta < 0) {
					scale /= 2;
				}
				make_set(sets, setIter, active_threads, max_threads, scale, window.getSize().x, window.getSize().y, sf::Vector2f(event.mouseWheelScroll.x, event.mouseWheelScroll.y), last_shift, last_scale);
				//cout << event.mouseWheelScroll.x << ", " << event.mouseWheelScroll.y << endl;
				//60.54, 495.55
				//500,500
				//event.mouseWheelScroll.x, event.mouseWheelScroll.y
			}
		}
		for (auto& th : active_threads) {
			if (th.joinable())
				th.join();
		}
		//RENDER--------------------------------------------------------------
		window.clear(bgColor);
		for (setIter = sets.begin(); setIter != sets.end(); setIter++) {
			totalPoints += (*setIter).getVertexCount();
			window.draw(*setIter);
		}
		//cout << totalPoints << endl;
		totalPoints = 0;
		/*window.draw(dot);
		window.draw(root1);
		window.draw(root2);
		window.draw(root3);*/
		window.display();
	}
	for (auto& th : active_threads) {
		if (th.joinable())
			th.join();
	}
}