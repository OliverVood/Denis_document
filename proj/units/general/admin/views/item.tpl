<?php

	namespace Proj\Admin\Templates\General;

	use Base\Templates\Template;

	abstract class Item {

		public static function ToVar(string $item): string {
			Template::Start();
			self::Render($item);
			return Template::Read();
		}

		public static function Render(string $item): void { ?>
			<li><?= $item; ?></li>
		<?php }

	}