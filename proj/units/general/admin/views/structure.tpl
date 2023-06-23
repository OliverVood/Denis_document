<?php

	namespace Proj\Admin\Templates\General;

	use Base\Templates\Template;

	abstract class Structure {

		public static function ToVar(array $items): string {
			Template::Start();
			self::Render($items);
			return Template::Read();
		}

		public static function Render(array $items): void { ?>
			<h1>Структура базы данных</h1>
			<div id = "structure"></div>
		<?php }

	}