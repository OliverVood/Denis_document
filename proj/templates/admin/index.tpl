<?php

	namespace Admin\Templates;

	use Base\Templates\View;
	use Admin\Templates\Layout;

	class Template extends View {

		public function ToVar() {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?><!doctype html>
			<html lang  = "ru">
				<head>
					<meta charset = "UTF-8">
					<meta name = "viewport" content = "width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
					<meta http-equiv = "X-UA-Compatible" content = "ie=edge">
					<title>Document</title>
					<?php Layout::BrowseStylesheets(); ?>
				</head>
				<body><? $this->RenderSections(); ?></body>
			</html>
		<?php }

		public function RenderSections() { ?>
			<header><?php Layout::instance()->header->Browse(); ?></header>
			<div>
				<menu><?php Layout::instance()->menu->Browse(); ?></menu>
				<main><?php Layout::instance()->main->Browse(); ?></main>
			</div>
			<footer><?php Layout::instance()->footer->Browse(); ?></footer>
		<?php }

	}