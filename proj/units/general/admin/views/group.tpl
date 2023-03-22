<?php

	namespace Proj\Admin\Templates\General;

	require 'item.tpl';

	use Base\Templates\Template;

	abstract class Group {

		public static function ToVar(string $title, array $items): string {
			Template::Start();
			self::Render($title, $items);
			return Template::Read();
		}

		public static function Render(string $title, array $items): void { ?>
			<li>
				<span>
					<?= $title; ?>
					<ul>
						<?php foreach ($items as $item) { Item::Render($item); } ?>
					</ul>
				</span>
			</li>
		<?php }

	}