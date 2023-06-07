<?php

	namespace Proj\Site\Templates\Changes;

	use Base\Templates\Buffering;
	use Proj\Units\Consts;

	abstract class Show {

		public static function ToVar(array $data, array $list): string {
			Buffering::Start();
			self::Render($data, $list);
			return Buffering::Read();
		}

		public static function Render(array $data, array $list): void { ?>
			<div class = "view changes show">
				<div class = "grid col_1">
					<div>
						<h1><?= $data['header']; ?></h1>
					</div>
				</div>
				<div class = "list">
					<?php foreach ($list as $item) self::RenderChange($item); ?>
				</div>
				<div class = "data publish"><?= $data['datepb']; ?></div>
			</div>
		<?php }

		private static function RenderChange($item): void {
			$background = $item['cover'] ? 'style = "background-image: url(' . Consts\Changes::PATH_COVER_RELATIVE . $item['cover'] . ');"' : '';
		?>
			<div class = "view change item">
				<div class = "cover"<?= $background; ?>></div>
				<div class = "wrap">
					<div class = "header"><?= $item['header']; ?></div>
					<div class = "content"><?= $item['content']; ?></div>
				</div>
			</div>
		<?php }

	}