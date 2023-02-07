<?php

	namespace Proj\Site\Templates\Changes;

	use Base\Templates\View;
//	use Proj\Units\Consts\Changes;

	class Show extends View {

		public function ToVar(array $data, array $list): string {
			$this->Start();
			$this->Render($data, $list);
			return $this->Read();
		}

		public function Render(array $data, array $list) {
//			$background = $data['cover'] ? 'style = "background-image: url(' . Changes::PATH_COVER_RELATIVE . $data['cover'] . ');"' : '';
		?>
			<div class = "view changes show">
				<h1><?= $data['header']; ?></h1>
<?php //<!--				<div class = "cover"--><?//= $background; ? ><!--></div>--> ?>
<!--				<div class = "content">--><?//= $data['content']; ?><!--</div>-->
				<div class = "data publish"><?= $data['datepb']; ?></div>
			</div>
		<?php Debug($list); }

	}